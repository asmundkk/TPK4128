#!/usr/bin/env python3

import numpy as np
import time, sched
from copy import copy

import rospy #  import rclpy
#  from rospy.node import init_node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
#  from control_interfaces.msg import Image
#  import sensor_msgs.image_encodings

import cv2 as cv

class Camera(object):
    def __init__(self):

        # Implement this constructor that opens a webcam and stores it in self._camera
        self._camera = cv.VideoCapture(0)

    def capture(self):

        print("constructor initialised")

        if not self._camera.isOpened():
            print("Cannot open camera")
            exit()
        #  while True:
        # Capture frame-by-frame
        ret, frame = self._camera.read()
        #      # if frame is read correctly ret is True
        if not ret:
            print("Can't receive frame (stream end?). Exiting ...")
            #  break
            # Our operations on the frame come here
            #  gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
            # Display the resulting frame
            #  cv.imshow('frame', gray)
            #  if cv.waitKey(1) == ord('q'):
                #  break

        return frame

    def __del__(self):

        # Implement this destructor. Remember to free the camera.
        self._camera.release()
        cv.destroyAllWindows()

class OpenCVCameraNode():

    def __init__(self):
        #  super().__init__('opencv_camera_node')
        self._pub = rospy.Publisher('image', Image, queue_size = 10)
        self._camera = Camera()
        self._t0 = None
        self._bridge = CvBridge()
        #  Timer(Duration(0.1), my_callback)
        self.time_interval = 0.1        # time period [s]

        #  while not rospy.is_shutdown():

        self.timer = rospy.Timer(rospy.Duration(self.time_interval), self.timer_callback)

        #  rospy.spin()
        #  = sched.scheduler(time.time, time.sleep)

    def timer_callback(self, timer):
        #  print 'Timer called at ' + str(event.current_real)
        print("entering callback")
        cv_image = self._camera.capture()
        #  img_cap = np.append('b', img_cap)
        print(type(cv_image))
        #  img_msg = Image(height = 480, width = 640, encoding = "rgb8", is_bigendian = 0, step = 640 * 8,  data = img_cap)
        #  img_msg = Image()
        #  img_msg.height = 480
        #  img_msg.width = 640
        #  img_msg.encoding = "rgb8"
        #  img_msg.is_bigendian =
        #  img_msg.

        #  correction = 0.1 * (np.sin(3.0 * (time.time() - self._t0)))
        #  command_msg.command[0] = self._initial_position[0] + correction

        #  image_message = bridge.cv2_to_imgmsg(cv_image, encoding="passthrough")
        self._pub.publish(self._bridge.cv2_to_imgmsg(cv_image, "rgb8")) # "bgr8"
        #  self._pub.publish([image_messagimage_message])

    #  def do_something(sc):
    #      print("Doing stuff...")
        # do your stuff
        #  s.enter(0.1, 1, do_something, (sc,))

    #  s.enter(0.1, 1, do_something, (s,))
    #  s.run()

    #  def _callback(self, msg):
    #      if self._t0 is None:
    #          self._t0 = time.time()
    #          self._initial_position = copy(msg.position)


def main(args=None):
    #  rospy.init(args=args)
    print("entering main")
    rospy.init_node('open_cv_camera_node')
    try :

        OpenCVCameraNode()
        rospy.spin()

    except rospy.ROSInterruptException:

        print("exception thrown")
    #  rospy.spin()

    #  opencv_camera_node.destroy_node(), has to be removed because the class is no longer a Node
    #  rospy.on_shutdown()


if __name__ == '__main__':
    main()
