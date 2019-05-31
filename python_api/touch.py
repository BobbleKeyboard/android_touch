#!/usr/bin/python3

import urllib.request
import json
import math
import types

class TouchBuilder:
    # TODO: Ensure that max height and max width is givenchmod 
    def __init__(self):
        self.json_data = []

    def commit(self):
        self.json_data.append({"type": "commit"})
        return self
    def down(self, x,y,n=0,p=50):
        self.json_data.append({"type": "down", "contact": n, "x": x, "y": y, "pressure": p})
        return self
    def multidown(self, points, p=50): # Expects array of tuple
        # TODO: Check if its array of tuples
        for finger in range(len(points)):
            self.down(points[finger][0],points[finger][1],finger)
        return self
    def up(self, n=0):
        self.json_data.append({"type": "up", "contact": n})
        return self
    def multiup(self, fingers):
        for i in range(fingers):
            self.up(i)
        return self
    def move(self, x,y,n=0,p=50):
        self.json_data.append({"type": "move", "contact": n, "x": x, "y": y, "pressure": p})
        return self
    def multimove(self, points,p=50):
        for finger in range(len(points)):
            self.move(points[finger][0], points[finger][1], finger)
        return self
    def delay(self, time_ms=100):
        self.json_data.append({"type": "delay", "value": time_ms})
        return self
    def build(self):
        return self.json_data
    def reset(self): # To reuse same variable
        self.json_data = []
        return self

class TouchActionBuilder:
    def __init__(self, tb=None):
        if tb:
            self.touch = tb 
        else:
            self.touch = TouchBuilder()

        self.double_tap_time_ms = 400

    # Send command to android_touch server
    def send_commands(self, commands, print_json=False):
        data=json.dumps(commands).encode('utf-8')
        req = urllib.request.Request('http://localhost:9889', data=data,
                             headers={'content-type': 'application/json'})
        urllib.request.urlopen(req)    
        if print_json:
            print(json.dumps(commands))

    # Used to execute the built action
    def execute(self, print_json=False):
        self.send_commands(self.touch.build(), print_json)
        return self
    
    # This will execute the built action and reset the action for further use of object
    def execute_and_reset(self, print_json=False):
        self.execute(print_json)
        self.reset()
        return self

    def reset(self):
        self.touch.reset()
        return self
    def delay(self, time_ms=100):
        self.touch.delay(time_ms)
        return self

    # Tested
    def tap(self, x,y, delay_ms=0): # Executes single tap
        self.touch.down(x,y).commit().delay(delay_ms).up().commit()
        return self

    # Tested
    def multifinger_tap(self, points, delay_ms=0): # Accepts array of tuple and execute multi funger tap
        # TODO: Make sure points is array of tuple
        self.touch.multidown(points).commit().delay(delay_ms).multiup(len(points)).commit()
        return self

    # Tested
    def doubletap(self, x, y):
        self.tap(x, y).delay(self.double_tap_time_ms).tap(x, y)
        return self

    # Tested
    def multifinger_doubletap(self, points): # Accepts array of tuple and execute multi funger tap
        # TODO: Make sure points is array of tuple
        self.multifinger_tap(points).delay(self.double_tap_time_ms).multifinger_tap(points)
        return self
        
    # Tested
    def ntap(self, x, y, n, delay_ms=100):
        for i in range(n):
            if i == 0:
                self.tap(x, y)
            else:
                self.delay(delay_ms).tap(x, y)
        return self

    # Tested
    def multifinger_ntap(self, points, n, delay_ms=100):
        for i in range(n):
            if i == 0:
                self.multifinger_tap(points)
            else:
                self.delay(delay_ms).multifinger_tap(points)
        return self
    
    def _move_line(self, x1, y1, x2, y2, steps=50, step_delay_ms=10, long_press_ms=0):
        # Prevent divided by 0 
        # TODO: Update line formula instead of hacking
        if x2 == x1:
            x2=x1+1
        
        m = float((y2-y1)/(x2-x1))
        c = (x2*y1-x1*y2)/(x2-x1)

        # Loop and move slightly
        if math.fabs(y2-y2) > math.fabs(x2-x1):
            step = (y2-y1)/steps
            for i in range(steps):
                y = y1+(i+1)*step
                x = (y - c)/m
                self.touch.move(x,y).commit().delay(step_delay_ms)  
        else:
            step = (x2-x1)/steps
            for i in range(steps):
                x = x1+(i+1)*step
                y = m*x + c
                self.touch.move(x,y).commit().delay(step_delay_ms)

        return self

    # Tested
    def swipe_line(self, x1, y1, x2, y2, steps=50, step_delay_ms=10, long_press_ms=0):
        self.touch.down(x1,y1).commit()
        if long_press_ms > 0:
            self.touch.delay(long_press_ms)
        self._move_line(x1, y1, x2, y2, steps, step_delay_ms, long_press_ms)
        self.touch.up().commit()
        return self

    # Tested
    def longpress_and_swipe_line(self, x1, y1, x2, y2, long_press_ms=1000):
        self.swipe_line(x1, y1, x2, y2, long_press_ms=long_press_ms)
        return self

    # Tested
    def swipe_nline(self, points, steps=50, steps_delay_ms=10, long_press_ms=0): # Points is array of tupples(x,y) 
        if len(points) > 1:
            self.touch.down(points[0][0], points[0][1]).commit()
            if long_press_ms > 0:
                self.touch.delay(long_press_ms)
            for i in range(len(points)-1):
                self._move_line(points[i][0], points[i][1], points[i+1][0], points[i+1][1], steps, steps_delay_ms)
            self.touch.up().commit()

        return self

    # Longpress and then start swiping 
    def longpress_swipe_nline(self, points, steps=50, steps_delay_ms=10, long_press_ms=1000): # Points is array of tupples(x,y) 
        self.swipe_nline(points, steps, steps_delay_ms, long_press_ms)
        return self
