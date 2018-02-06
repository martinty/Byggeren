#ifndef SLIDER_H_
#define SLIDER_H_

typedef enum SIDE_T{RIGHT = 3, LEFT = 4} SIDE_T;
int slider_position(SIDE_T side);
int slider_button(SIDE_T side);

#endif /* SLIDER_H_ */