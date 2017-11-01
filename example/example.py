import urllib2
import json
import math


def send_commands(commands):
    req = urllib2.Request('http://localhost:8080')
    urllib2.urlopen(req, json.dumps(commands))


def generate_circle_gesture(x, y, r, num_points=100, delay=100):
    if num_points > 2:
        points = [(int(math.cos(2 * math.pi / num_points * index) * r + x),
                   int(math.sin(2 * math.pi / num_points * index) * r + y))
                  for index in xrange(0, num_points + 1)]

        is_started = False
        json_data = []
        for point in points:
            if not is_started:
                is_started = True
                json_data.append({"type": "down", "contact": 0, "x": point[0], "y": point[1], "pressure": 50})
                json_data.append({"type": "commit"})
                json_data.append({"type": "delay", "value": delay})
            else:
                json_data.append({"type": "move", "contact": 0, "x": point[0], "y": point[1], "pressure": 50})
                json_data.append({"type": "commit"})
                json_data.append({"type": "delay", "value": delay})

        json_data.append({"type": "up", "contact": 0})
        json_data.append({"type": "commit"})

        send_commands(json_data)


if __name__ == '__main__':
    for r in xrange(100, 500, 100):
        generate_circle_gesture(1024 / 2, 1920 / 2, r, 100, 50)
