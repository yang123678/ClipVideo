# -*- coding: utf-8 -*-
"""
# --------------------------------------------------------
# @Project: Ultra-Light-Fast-Generic-Face-Detector-1MB
# @Author : panjq
# @E-mail : pan_jinquan@163.com
# @Date   : 2020-09-04 16:10:13
# --------------------------------------------------------
"""

import cv2
import torch
import numpy as np

from lib.hm_detector_v1.ultra_light_detector.nets.ssd.mb_tiny_fd import create_mb_tiny_slim_fd
from lib.hm_detector_v1.ultra_light_detector.nets.ssd.mb_tiny_RFB_fd import create_mb_tiny_rfb_fd
from lib.hm_detector_v1.ultra_light_detector.nets.ssd.mb_tiny_RFB_landms import create_mb_tiny_rfb_landms
from lib.hm_detector_v1.ultra_light_detector.nets.ssd.mobilenet_v2_ssd_lite import create_mobilenetv2_ssd_lite
from lib.hm_detector_v1.ultra_light_detector.nets.ssd.mobilenet_v2_ssd_landms import create_mobilenetv2_ssd_landms


def build_net(net_type, prior_boxes, num_classes, width_mult, is_test=False, device="cuda:0"):
    if net_type.lower() == 'slim'.lower():
        create_net = create_mb_tiny_slim_fd
    elif net_type.lower() == 'RFB'.lower():
        create_net = create_mb_tiny_rfb_fd
    elif net_type.lower() == 'mbv2'.lower():
        create_net = create_mobilenetv2_ssd_lite
    elif net_type.lower() == 'RFB_landms'.lower():
        create_net = create_mb_tiny_rfb_landms
    elif net_type.lower() == 'mbv2_landms'.lower():
        create_net = create_mobilenetv2_ssd_landms
    else:
        create_net = None
        raise Exception("The net type is wrong.")


    net = create_net(prior_boxes=prior_boxes,
                     num_classes=num_classes,
                     is_test=is_test,
                     device=device,
                     width_mult=width_mult)
    return net
