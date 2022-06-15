#ifndef DISPLAYFORDIRDETECTION_H
#define DISPLAYFORDIRDETECTION_H
#include <opencv2/core/core.hpp>
#include "dirdetectionparams.h"

void DrawTilesOnImage(cv::Mat ImIn, DirDetectionParams params);
void DrawTilesOnImage(cv::Mat ImIn, bool showTilesOnImage, int tileShape, int tileOffsetX, int inttileOffsetY,
                      int tileSize, int tileShift, int tileLineWidth);
void ShowDirection(cv::Mat ImToShow, int y, int x, float direction, int lineWidth, int lineLength, double scale = 1.0 , cv::Scalar color = cv::Scalar(0.0, 0.0, 0.0, 0.0));
void ShowDirectionGray(cv::Mat ImToShow, int y, int x, float direction, int lineWidth, int lineLength, double scale = 1.0 , cv::Scalar color = cv::Scalar(0.0, 0.0, 255.0, 0.0));


#endif // DISPLAYFORDIRDETECTION_H
