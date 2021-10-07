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

using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned long;
using uint64_t = unsigned long long;
using int8_t =  char;
using int16_t = short;
using int32_t = long;
using int64_t = long long;

static_assert(sizeof(uint8_t) == 1);
static_assert(sizeof(uint16_t) == 2);
static_assert(sizeof(uint32_t) == 4);
static_assert(sizeof(uint64_t) == 8);
static_assert(sizeof(int8_t) == 1);
static_assert(sizeof(int16_t) == 2);
static_assert(sizeof(int32_t) == 4);
static_assert(sizeof(int64_t) == 8);

using size_t = uint32_t;

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
