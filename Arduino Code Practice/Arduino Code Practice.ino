//Inclusive
const int LOWER = 0;
const int UPPER = 100;

void setup() {
  Serial.begin(9600);
  Serial.print("Size of Array?: ");
}

void fillArray(int arr[], int size){
  srand(millis());
  for (int i = 0; i < size; i++){
    arr[i] = (rand() % (UPPER+1-LOWER))+LOWER;
  }
}

void printArray(int arr[], int size){
  Serial.print("[ ");
  for (int i = 0; i < size; i++){
    Serial.print(arr[i]);
    if(i != size-1)
    Serial.print(" , ");
  }
  Serial.println(" ]");
}

void sortArray(int arr[], int size){
  int temp;
  bool done = true;
  do{
    done = true;
    for (int i = 1; i < size; i++){
      if(arr[i-1] > arr[i]){
        done = false;
        temp = arr[i-1];
        arr[i-1]=arr[i];
        arr[i]=temp;
      }
    }
  } while (!done);
}

int maxVal(int arr[], int size){
  return arr[size-1];
}

float meanVal(int arr[], int size){
  float sum=0;
  for (int i = 0; i < size; i++){
    sum += arr[i];
  }
  return sum/(float)size;  
}

int minVal(int arr[]){
  return arr[0];
}


void loop() {
  int min, max;
  float mean;

  while(Serial.available() == 0){}
  int size = Serial.parseInt();
  if(size != 0){
   Serial.println(size);
   int arr[size];
   fillArray(arr,size);
   Serial.print("Random:\t");
   printArray(arr, size);
   sortArray(arr, size);
   Serial.print("Sorted:\t");
   printArray(arr, size);
   max = maxVal(arr, size);
   min = minVal(arr);
   mean = meanVal(arr,size);

   Serial.print("Min: ");
   Serial.println(min);
   Serial.print("Max: ");
   Serial.println(max);
   Serial.print("Mean: ");
   Serial.println(mean);
   Serial.println();
   Serial.print("Size of Array?: ");
  }
}
