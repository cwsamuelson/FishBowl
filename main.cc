const char* temp = "test string";

union UART{
  struct _t{
    unsigned char SEND;
  } t;
  unsigned char RAW[0x0100];
};

UART*const UART0 = reinterpret_cast<UART*>(0x1000'0000);

void print(const char* text, UART*const uart){
  while(*text != '\0'){
    uart->t.SEND = *text;
    ++text;
  }
}

void println(const char* text, UART*const uart){
  print(text, uart);
  print("\n", uart);
}
void memcpy(unsigned char* destination, unsigned char* source, size_t length){
  while(length > 0){
    destination[length] = source[length];
    --length;
  }
}

int main(){
  println(temp, UART0);

  return 0;
}
