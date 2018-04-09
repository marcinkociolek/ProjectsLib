#ifndef DISPLAYFORDIRDETECTION_H
#define DISPLAYFORDIRDETECTION_H

void DrawTilesOnImage(cv::Mat ImIn, DirDetectionParams params);
void DrawTilesOnImage(cv::Mat ImIn, bool showTilesOnImage, int tileShape, int tileOffsetX, int inttileOffsetY,
                      int tileSize, int tileShift, int tileLineWidth);
void ShowDirection(cv::Mat ImToShow, int y, int x, float direction, int lineWidth, int lineLength);

#endif // DISPLAYFORDIRDETECTION_H
