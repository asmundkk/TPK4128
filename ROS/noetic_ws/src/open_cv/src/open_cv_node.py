#!/usr/bin/env python

import numpy as np
import time, sched
from copy import copy

import rospy #  import rclpy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

import cv2 as cv

class Camera(object):
    def __init__(self):

        self._camera = cv.VideoCapture(0)

    def capture(self):

        if not self._camera.isOpened():
            print("Cannot open camera")
            exit()
        ret, frame = self._camera.read()

        if not ret:
            print("Can't receive frame (stream end?). Exiting ...")
            exit()
        return frame

    def __del__(self):

        self._camera.release()
        cv.destroyAllWindows()

class OpenCVCameraNode():

    def __init__(self):
        #  super().__init__('opencv_camera_node')
        self._pub = rospy.Publisher('image', Image, queue_size = 10)
        self._camera = Camera()
        self._t0 = None
        self._bridge = CvBridge()
        self.time_interval = 0.1        # time period [s]

        self.timer = rospy.Timer(rospy.Duration(self.time_interval), self.timer_callback)

    def timer_callback(self, timer):

        cv_image = self._camera.capture()
        self._pub.publish(self._bridge.cv2_to_imgmsg(cv_image, "bgr8")) # "rgb8"

def main(args=None):

    rospy.init_node('open_cv_camera_node')
    try :

        OpenCVCameraNode()
        rospy.spin()

    except rospy.ROSInterruptException:

        print("exception thrown")

if __name__ == '__main__':
    main()
