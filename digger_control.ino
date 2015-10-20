
int i = 0;

// Number of milliseconds to turn motor on in a sequence
int TIME_ON = 10;
int FREQUENCY = 30; // Number of milliseconds per cycle
int TIME_OFF = FREQUENCY - TIME_ON;
// Number of cycles to run in each function
int CYCLES_TO_RUN = 1000 / FREQUENCY;
volatile bool eStop = false;
int N_ITERATIONS = 5;

int LEFT_TRACK_FORWARD = D3;
int RIGHT_TRACK_FORWARD = D2;
int LEFT_TRACK_ENABLE = D4;
int RIGHT_TRACK_ENABLE = D5;

int ARM_UP = D0;
int BUCKET_OUT = D1;

int BUCKET_ENABLE = A0;
int ARM_ENABLE = A1;

int ENABLE_ALL = D7;


int test(String args){
    digitalWrite(LEFT_TRACK_ENABLE, HIGH);
    digitalWrite(LEFT_TRACK_FORWARD, LOW);
    delay(100);
    right_forwards(args);
    right_backwards(args);
    delay(100);
    
    digitalWrite(LEFT_TRACK_FORWARD, HIGH);
    delay(100);
    right_forwards(args);
    right_backwards(args);
    delay(100);
    
    left_forwards(args);
    left_backwards(args);
    right_forwards(args);
    right_backwards(args);
    
    digitalWrite(LEFT_TRACK_ENABLE, LOW);
}


int left_forwards(String args){
    digitalWrite(LEFT_TRACK_FORWARD, LOW); // wiring fix
    return _run_tracks(2, true, false);
}

int left_backwards(String args){
    digitalWrite(LEFT_TRACK_FORWARD, HIGH); // wiring fix
    return _run_tracks(2, true, false);
}

int right_forwards(String args){
    digitalWrite(RIGHT_TRACK_FORWARD, LOW); // wiring fix
    return _run_tracks(2, false, true);
}

int right_backwards(String args){
    digitalWrite(RIGHT_TRACK_FORWARD, HIGH); // wiring fix
    return _run_tracks(2, false, true);
}


int _run_tracks(int iterations, bool left, bool right){
    return _run_tracks(iterations, left, right, 1);
}

int _run_tracks(int iterations, bool left, bool right, int on_multiplier){
    // Runs tracks however they are setup
    int result = 0;
    for (int jn=0; jn< iterations && result == 0; jn++){
        for (int i=0; i<CYCLES_TO_RUN; i++){
            if (left) digitalWrite(LEFT_TRACK_ENABLE, HIGH);
            if (right) digitalWrite(RIGHT_TRACK_ENABLE, HIGH);
            delay(TIME_ON * on_multiplier);
            if (left) digitalWrite(LEFT_TRACK_ENABLE, LOW);
            if (right) digitalWrite(RIGHT_TRACK_ENABLE, LOW);
            delay(TIME_OFF);
    
            if (eStop == true){
                //return 1;  // Note: remember to set motors low
            }
        }
    }
    return 0;
}

int forwards(String args){
    eStop = false;
    digitalWrite(LEFT_TRACK_FORWARD, LOW); // wiring fix
    digitalWrite(RIGHT_TRACK_FORWARD, LOW);
    return _run_tracks(2, true, true);
}

int backwards(String args){
    eStop = false;
    digitalWrite(LEFT_TRACK_FORWARD, HIGH); // wiring fix
    digitalWrite(RIGHT_TRACK_FORWARD, HIGH);
    return _run_tracks(2, true, true);
}

int right(String args){
    digitalWrite(LEFT_TRACK_FORWARD, LOW); // wiring fix
    return _run_tracks(1, true, false, 5);
}

int left(String args){
    digitalWrite(RIGHT_TRACK_FORWARD, LOW); // wiring fix
    return _run_tracks(1, false, true, 5);
}

void emergency_stop(){
    eStop = true;
}


void reset_motors(){
    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
}

int arm_test(String args){
    // Arm
    for (int i=0; i< 0; i++){
        digitalWrite(ARM_ENABLE, HIGH);
        digitalWrite(ARM_UP, HIGH);
        delay(TIME_ON * 10);
        /*digitalWrite(ARM_UP, LOW);
        delay(TIME_ON * 10);
        */
        digitalWrite(ARM_ENABLE, LOW);
    }
    
    // Bucket
    
    for (int i=0; i< 10; i++){
        digitalWrite(BUCKET_ENABLE, HIGH);
        digitalWrite(BUCKET_OUT, HIGH);
        delay(TIME_ON * 50);
        digitalWrite(BUCKET_OUT, LOW);
        delay(TIME_ON * 50);
        digitalWrite(BUCKET_ENABLE, LOW);
    }
    return 0;
}


void setup() {
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    
    reset_motors();
    
    // Expose function
    Spark.function("arm", arm_test);
    Spark.function("forwards", forwards);
    Spark.function("backwards", backwards);
    Spark.function("left", left);
    Spark.function("right", right);

    //Spark.function("arm_down", arm_down);
}
