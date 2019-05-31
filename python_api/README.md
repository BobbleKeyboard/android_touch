# Android Touch Python API

This API provides easy way to interact with the (android) touch server running on the device.  
Have a look at the touch_test.py to understand its usage.  

Most common actions are available at `TouchActionBuilder` for example `tap`, `double tap`, `swipe`, `multi finder tap`. 
Complex actions can be built using `TouchBuilder`  

#### Example of simple actions
1. Single finger tap
```
tab = TouchActionBuilder()
tab.tap(10, 10).execute()
```

2. Swipe line
```
tab = TouchActionBuilder()
tab.swipe_line(10, 10, 100, 100).execute()
```

#### Example of complex action
1. Touch down with one finger and keep it there for 500ms
2. Touch down with second finger while keeping the first finger as it is
3. Pick up both the fingers

```
tb = TouchBuilder()
tb.down(10,10, 0).commit().delay(500)
tb.down(100,100, 1).commit()
tb.multiup(2).commit()

tab = TouchActionBuilder(tb)
tab.execute()
```

__Look at `touch_test.py` for more examples__