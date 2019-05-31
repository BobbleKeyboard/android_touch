from touch import TouchActionBuilder

x1 = 10
y1 = 10

x2_1, y2_1 = 2800, 500
x2_2, y2_2 = 3500, 500
x3_1, y3_1 = 3900, 1000

points1 = [(100,10), (100, 1000)]
points2 = [(x2_1,y2_1), (x2_2, y2_2)]
points3 = [(x2_1,y2_1), (x2_2, y2_2), (x3_1, y3_1)]

one_second = 1000
half_econd = 500

th = TouchActionBuilder()
th.tap(x1, y1, one_second).execute_and_reset()
# th.multifinger_tap(points1, 1000).execute_and_reset()
# th.doubletap(10,10).execute_and_reset()
# th.multifinger_doubletap(points2).execute_and_reset()
# th.ntap(x2_2, y2_2, 8, 250).execute_and_reset()
# th.multifinger_ntap(points2, 5, 250).execute_and_reset()
# th.swipe_line(x2_1, y2_2, x2_1, y2_2+200).execute_and_reset()
# th.longpress_and_swipe_line(x2_1, y2_1, x2_2, y2_2).execute_and_reset()
# th.swipe_nline(points3, 50, 5).execute_and_reset()
# th.longpress_swipe_nline(points3).execute_and_reset()