//Arduino Pins
const int joystickXInputPin = A1; //Joystick Inputpin X-axis
const int joystickYInputPin = A0; //Joystick Inputpin Y-axis

const int posXpwmPin = 10; //Pin that moves the plane to the right
const int negXpwmPin = 6; //Pin that moves the plane to the left
const int posYpwmPin = 9; //Pin that moves the plane up
const int negYpwmPin = 11; //Pin that moves the plane down

const int buttonBorderLeftPin = 2;
const int buttonBorderRightPin = 4;
const int buttonBorderTopPin = 7;
const int buttonBorderBottomPin = 8;

//Joystick callibration
int joystickXMaxValue = 955; //Maximum value that joystickXInputPin reads
int joystickXMinValue = 210; //Minimum value that joystickXInputPin reads
int joystickXCenterValue = 516; //Value that int joystickXInputPin reads at default joystick position
int joystickXCenterTollerance = 6; //Tollerance for joystickXCenterValue

int joystickYMaxValue = 890; //Maximum value that joystickYInputPin reads
int joystickYMinValue = 155; //Minimum value that joystickYInputPin reads
int joystickYCenterValue = 522; //Value that int joystickYInputPin reads at default joystick position
int joystickYCenterTollerance = 12; //Tollerance for joystickYCenterValue


int sensorValueX = 0;
int sensorValueY = 0;

int outputValueX = 0;
int outputValueY = 0;

void setup() {
    Serial.begin(9600); //

    pinMode(buttonBorderLeftPin, INPUT);
    pinMode(buttonBorderRightPin, INPUT);
    pinMode(buttonBorderTopPin, INPUT);
    pinMode(buttonBorderBottomPin, INPUT);
}

void loop() {
    //X-movement
    sensorValueX = analogRead(joystickXInputPin);

    if (sensorValueX > (joystickXCenterValue + joystickXCenterTollerance) || digitalRead(buttonBorderLeftPin) == LOW) {
        outputValueX = map(sensorValueX, joystickXCenterValue + joystickXCenterTollerance, joystickXMaxValue, 0, 255); 
        analogWrite(negXpwmPin, 0);
        analogWrite(posXpwmPin, outputValueX);
    }
    else if (sensorValueX < (joystickXCenterValue - joystickXCenterTollerance) || digitalRead(buttonBorderRightPin) == LOW) {
        outputValueX = map(sensorValueX, joystickXCenterValue - joystickXCenterTollerance, joystickYMinValue, 0, 255);
        analogWrite(posXpwmPin, 0);
        analogWrite(negXpwmPin, outputValueX);
    }
    else{
        outputValueX = 0;
        analogWrite(posXpwmPin, outputValueX);
        analogWrite(negXpwmPin, outputValueX);
    }

    //Y-movement
    sensorValueY = analogRead(joystickYInputPin);

    if (sensorValueY > (joystickYCenterValue + joystickYCenterTollerance) || digitalRead(buttonBorderTopPin) == LOW) {
        outputValueY = map(sensorValueY, joystickYCenterValue + joystickYCenterTollerance, joystickYMaxValue, 0, 255);
        analogWrite(negYpwmPin, 0);
        analogWrite(posYpwmPin, outputValueY);
    }
    else if (sensorValueY < (joystickYCenterValue - joystickYCenterTollerance) || digitalRead(buttonBorderBottomPin) == LOW) {
        outputValueY = map(sensorValueY, joystickYCenterValue - joystickYCenterTollerance, joystickYMinValue, 0, 255);
        analogWrite(posYpwmPin, 0);
        analogWrite(negYpwmPin, outputValueY);
    }
    else{
        outputValueY = 0;
        analogWrite(posYpwmPin, outputValueY);
        analogWrite(negYpwmPin, 0);
    }
    delay(1);
}