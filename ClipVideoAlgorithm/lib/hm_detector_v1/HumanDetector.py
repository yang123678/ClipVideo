import cv2
import numpy as np


class HumanDetector():

    def __init__(self, IN_conf):
        print("__init__.%s,IN_conf=%s" % (self.__class__.__name__, str(IN_conf)))

        weight_file = IN_conf.get("weight_file")
        self.detect_type = IN_conf.get("detect_type")
        self.device = IN_conf.get("device","cuda:0")

        candidate_size = IN_conf.get("candidate_size",200)
        prob_threshold = IN_conf.get("prob_threshold",0.6)
        iou_threshold = IN_conf.get("iou_threshold",0.3)

        if self.detect_type == "mtcnn":
            # sys.path.append(os.path.join(os.path.dirname(__file__), "mtcnn"))
            from lib.hm_detector_v1.mtcnn import mtcnn
            self.class_names = ["BACKGROUND", "face"]
            self.detector = mtcnn.MTCNN(device=self.device)

        elif self.detect_type == "ultra_face":
            # sys.path.append(os.path.join(os.path.dirname(__file__), "ultra_light_detector"))
            from lib.hm_detector_v1.ultra_light_detector import demo as ultra_detector
            self.class_names = ["BACKGROUND", "face"]

            net_type = "rfb"
            input_size = [640, 640]
            priors_type = "face"
            self.detector = ultra_detector.Detector(weight_file,
                                                    net_type=net_type,
                                                    input_size=input_size,
                                                    class_names=self.class_names,
                                                    priors_type=priors_type,
                                                    candidate_size=candidate_size,
                                                    iou_threshold=iou_threshold,
                                                    prob_threshold=prob_threshold,
                                                    device=self.device)
        elif self.detect_type == "ultra_person":
            # sys.path.append(os.path.join(os.path.dirname(__file__), "ultra_light_detector"))
            from lib.hm_detector_v1.ultra_light_detector import demo as ultra_detector
            self.class_names = ["BACKGROUND", "person"]
            net_type = "rfb"
            input_size = [640, 360]
            priors_type = "person"


            self.detector = ultra_detector.Detector(weight_file,
                                                    net_type=net_type,
                                                    input_size=input_size,
                                                    class_names=self.class_names,
                                                    priors_type=priors_type,
                                                    candidate_size=candidate_size,
                                                    iou_threshold=iou_threshold,
                                                    prob_threshold=prob_threshold,
                                                    device=self.device)
        elif self.detect_type == "ultra_face_person":
            # sys.path.append(os.path.join(os.path.dirname(__file__), "ultra_light_detector"))
            from lib.hm_detector_v1.ultra_light_detector import demo as ultra_detector
            self.class_names = ["BACKGROUND", "face", "person"]

            net_type = "mbv2"
            input_size = [640, 360]
            priors_type = "face_person"
            self.detector = ultra_detector.Detector(weight_file,
                                                    net_type=net_type,
                                                    input_size=input_size,
                                                    class_names=self.class_names,
                                                    priors_type=priors_type,
                                                    candidate_size=candidate_size,
                                                    iou_threshold=iou_threshold,
                                                    prob_threshold=prob_threshold,
                                                    device=self.device)
        elif self.detect_type == "ultra_person_pig":
            # sys.path.append(os.path.join(os.path.dirname(__file__), "ultra_light_detector"))
            from lib.hm_detector_v1.ultra_light_detector import demo as ultra_detector
            self.class_names = ["BACKGROUND", "person", "pig"]
            net_type = "mbv2"
            input_size = [416, 416]
            priors_type = "person_pig"
            self.detector = ultra_detector.Detector(weight_file,
                                                    net_type=net_type,
                                                    input_size=input_size,
                                                    class_names=self.class_names,
                                                    priors_type=priors_type,
                                                    candidate_size=candidate_size,
                                                    iou_threshold=iou_threshold,
                                                    prob_threshold=prob_threshold,
                                                    device=self.device)
        else:
            raise Exception("detect_type:{}".format(self.detect_type))
    def __del__(self):
        print("__del__.%s" % (self.__class__.__name__))
    def standard_detect(self, image):
        """
        @param image:
        @return:
        """
        detect_num = 0   # 检测目标数量
        detect_data = [] # 检测目标位置
        detect_msg = ""
        try:
            bbox_score, labels = self.detect(image)
            boxes = bbox_score[:, 0:4]
            scores = bbox_score[:, 4:5]

            if boxes.shape[0] > 0:# 检测到了人体坐标
                detect_num = boxes.shape[0]
                for i in range(detect_num):
                    x1 = int(boxes[i, 0])
                    y1 = int(boxes[i, 1])
                    x2 = int(boxes[i, 2])
                    y2 = int(boxes[i, 3])
                    location = {
                        "x1": x1,
                        "y1": y1,
                        "x2": x2,
                        "y2": y2
                    }
                    detect_data.append({
                        "class_name":"unknown",
                        "location": location,
                        "score": float("%.2f" % (float(scores[i, 0])))
                    })
        except Exception as e:
            detect_msg = str(e)

        return detect_num,detect_data,detect_msg

    def detect(self, rgb_image):
        """
        :param rgb_image:
        :param isshow:
        :return:
        """
        bbox_score = np.asarray([])
        if self.detect_type == "mtcnn":
            bbox_score, landmarks = self.detector.detect_image(rgb_image)
            labels = np.ones(shape=(len(bbox_score)), dtype=np.int32)

        elif "ultra" in self.detect_type:
            boxes, labels, probs = self.detector.detect_image(rgb_image, isshow=False)
            if len(boxes) > 0:
                bbox_score = np.hstack((boxes, probs.reshape(-1, 1)))
        else:
            raise Exception("Error:{}".format(self.detect_type))

        return bbox_score, labels


if __name__ == "__main__":
    import time
    url = 0
    url = "E:\\Project\\bxc\\BXC_ClipVideo\\data\\测试2.mp4"
    # import os
    # current_root = os.path.join(os.path.dirname(__file__))
    device = "cuda:0"


    conf = {
        "detect_type": "ultra_face",
        "weight_file":"../../weights/hm_detector_v1/pth/rfb_face_640_640.pth",
        "device":device
    }

    detector = HumanDetector(IN_conf=conf)
    # detector = HumanDetector(detect_type="mtcnn", device="cuda:0")
    capture = cv2.VideoCapture(url)
    while True:
        r, frame = capture.read()
        if r:
            frame = cv2.resize(frame, (1280, 720))

            t1 = time.time()
            detect_num, detect_data,detect_msg = detector.standard_detect(frame)
            t2 = time.time()
            print("detect spend %.3f (s)"%(t2 - t1), detect_num, detect_data)

            if detect_num > 0:
                for detect_item in detect_data:
                    loc = detect_item.get("location")
                    x1, y1, x2,y2 = loc.get("x1"), loc.get("y1"), loc.get("x2"), loc.get("y2")
                    cv2.rectangle(frame, (x1,y1), (x2,y2), (0, 255, 255), 2)

            cv2.imshow('test', frame)
            cv2.waitKey(1)

        else:
            print("读取%s结束" % str(url))
            break

    capture.release()
    cv2.destroyAllWindows()

