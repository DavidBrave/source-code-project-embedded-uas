// C++ code
//

//mode input arduino yang ingin digunakan
int mode = 1;

//output led yang digunakan
int biru = 2;
int hijau = 3;
int kuning = 4;
int merah = 5;

//output buzzer yang digunakan
int speaker = 6;

//input trigger, output echo dari ultrasonic distance sensor
int trigger = 7;
int echo = 8;


float waktu = 0;
float jarak = 0;
float kecepatan = 0.0343 / 2;
//kareba kita menggunakan ultrasonic distance sensor, maka kecepatan yang dipakai adalah kecepatan suara
//kecepatan suara = 343 m / s
//perhitungan pada arduino dilakukan dalam satuan micro, sehingga perlu kita konversi
//kecepatan suara = 0.0343 micrometer / microsecond
//waktu suara dibagi 2 karena suara harus ke target dan
//kembali ke sensor (waktu bolak-balik)

//angka inputan jarak jika menggunakan mode input
int jarak_input = 500;

void setup()
{
  //initializasi serial
  Serial.begin(9600);    
  
  //initializasi pin sebagai output atau input
  //led
  pinMode(biru, OUTPUT);
  pinMode(hijau, OUTPUT);
  pinMode(kuning, OUTPUT);
  pinMode(merah, OUTPUT);
  
  //buzzer
  pinMode(speaker, OUTPUT);
  
  //ultrasonic sensor
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
}

void loop()
{
  //mereset pengecekan ultrasonic sensor
  digitalWrite(trigger, LOW);
  delay(10);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  
  //waktu diambil dari hasil pantulan suara kembali dari benda
  //di depan ultrasonic sensor
  waktu = pulseIn(echo, HIGH);
  
  //rumus jarak sederhana
  //s = v * t
  //jarak = kecepatan * waktu
  jarak = kecepatan * waktu;
  
  //pengecekan jika nilai melebihi ambang batas float
  //sehingga jarak tidak mungkin negatif
  if (jarak < 0) {
   jarak = 0; 
  }
  
  //Serial.print("Jarak : ");
  //Serial.print(jarak);
  //Serial.println(" cm";
  
  //jarak dalam cm
  //range dari dokumen tertulis 3cm sampai 400cm
  //source https://www.arduino.cc/en/Tutorial/BuiltInExamples/Ping
  
  //tapi dari uji coba sekitar 3cm sampai 335cm
  
  
  //mode 0 = sensor based
  if (mode == 0) {
    
    //jika jarak jauh, tidak terjadi action apapun
    if (jarak > 300) {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, LOW);
      digitalWrite(speaker, LOW);
      
      delay(100);
    }
    //jarak mulai terlihat, led biru menyala
    else if (jarak > 220) {
      digitalWrite(biru, HIGH);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, LOW);
      digitalWrite(speaker, LOW);
      
      delay(100);
    }
    //jarak mulai dekat, led hijau menyala
    //buzzer berbunyi tiap 100ms
    else if (jarak > 140) {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, HIGH);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, LOW);
      
      digitalWrite(speaker, HIGH);
      delay(100);
      digitalWrite(speaker, LOW);
    }
    //jarak sudah dekat, led kuning menyala
    //buzzer berbunyi tiap 50ms
    else if (jarak > 60) {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, HIGH);
      digitalWrite(merah, LOW);
      
      for (int i = 0; i < 2; i++) {
        digitalWrite(speaker, HIGH);
        delay(50);
        digitalWrite(speaker, LOW);
      }
    }
    //jarak sangat dekat, led merah menyala
    //buzzer berbunyi tiap 20ms
    else {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, HIGH);
      
      for (int i = 0; i < 5; i++) {
        digitalWrite(speaker, HIGH);
        delay(20);
        digitalWrite(speaker, LOW);
      }
    }
  }
  
  
  
  //---------------------------------------------------\\
  
  
  
  
  //---------------------------------------------------\\
  
  //mode 1, input based
  if (mode == 1) {
    
    //jika terdapat input data, maka akan disimpan
    if (Serial.available() > 0) {
      
      //input data jarak diambil dari mengubah input serial
      //menjadi nilai integer
      jarak_input = Serial.parseInt();
      
      
      Serial.print("Jarak Input : ");
      Serial.print(jarak_input);
      Serial.println(" cm");
    }
    /*
    else {
      jarak_input -= 5;
      if (jarak_input < 0) {
         jarak_input = 0; 
      }
    }
    */
    
    
    //jika jarak jauh, tidak terjadi action apapun
    if (jarak_input > 300) {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, LOW);
      digitalWrite(speaker, LOW);
      
      delay(100);
    }
    //jarak mulai terlihat, led biru menyala
    else if (jarak_input > 220) {
      digitalWrite(biru, HIGH);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, LOW);
      digitalWrite(speaker, LOW);
      
      delay(100);
    }
    //jarak mulai dekat, led hijau menyala
    //buzzer berbunyi tiap 100ms
    else if (jarak_input > 140) {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, HIGH);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, LOW);
      
      digitalWrite(speaker, HIGH);
      delay(100);
      digitalWrite(speaker, LOW);
    }
    //jarak sudah dekat, led kuning menyala
    //buzzer berbunyi tiap 50ms
    else if (jarak_input > 60) {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, HIGH);
      digitalWrite(merah, LOW);
      
      for (int i = 0; i < 2; i++) {
        digitalWrite(speaker, HIGH);
        delay(50);
        digitalWrite(speaker, LOW);
      }
    }
    //jarak sangat dekat, led merah menyala
    //buzzer berbunyi tiap 20ms
    else if (jarak_input > 0) {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, HIGH);
      
      for (int i = 0; i < 5; i++) {
        digitalWrite(speaker, HIGH);
        delay(20);
        digitalWrite(speaker, LOW);
      }
    }
    else {
      digitalWrite(biru, LOW);
      digitalWrite(hijau, LOW);
      digitalWrite(kuning, LOW);
      digitalWrite(merah, LOW);
      digitalWrite(speaker, LOW);
    }
  }
  
  
  
}













