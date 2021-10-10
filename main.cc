#include <concepts>
#include <iterator>

using uint8_t = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned long;
using uint64_t = unsigned long long;
//using int8_t =  char;
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

//using size_t = uint32_t;

union UART_e{
  struct {
    // receive/transmit are the same address....
    union {
      union { // readonly
        volatile const unsigned char READ;
        volatile const unsigned char RBR;
      };
      union { // write only
        volatile unsigned char WRITE;
        volatile unsigned char THR;
      };
    };

    union{
      volatile unsigned char RAW;
      struct{
        volatile bool ERBFI:1;
        volatile bool ETBEI:1;
        volatile bool ELSI:1;
        volatile bool EDSSI:1;
        volatile unsigned char UNUSED:4;
      };
    } IER;

    union{
      union{ // read only
        volatile const unsigned char RAW;
        struct{
          volatile const bool InterruptPending:1;
          volatile const unsigned char InterruptID:3;
          volatile const unsigned char UNUSED:2;
          volatile const unsigned char FIFOsEnabled:2;
        };
      } IIR;

      union{ // write only
        volatile unsigned char RAW;
        struct{
          volatile bool FIFOEnable:1;
          volatile bool RxFIFOReset:1;
          volatile bool TxFIFOReset:1;
          volatile bool DMASelect:1;
          volatile unsigned char UNUSED:2;
          volatile bool LSB:1;
          volatile bool MSB:1;
        };
      } FCR;
    };

    union{
      volatile unsigned char RAW;
      struct{
        volatile unsigned char WLS:2;
        volatile bool STB:1;
        volatile bool PEN:1;
        volatile bool EPS:1;
        volatile bool StickParity:1;
        volatile bool SetBreak:1;
        volatile bool DLAB:1;
      };
    } LCR;

    union{
      volatile unsigned char RAW;
      struct{
        volatile bool DTR:1;
        volatile bool RTS:1;
        volatile bool OUT:2;
        volatile bool Loop:1;
        volatile unsigned char UNUSED:3;
      };
    } MCR;

    union{
      volatile unsigned char RAW;
      struct{
        volatile bool DR:1;
        volatile bool OE:1;
        volatile bool PE:1;
        volatile bool FE:1;
        volatile bool BI:1;
        volatile bool THRE:1;
        volatile bool TEMT:1;
        volatile bool RxFIFOErr:1;
      };
    } LSR;

    union{
      volatile unsigned char RAW;
      struct{
        volatile bool DCTS:1;
        volatile bool DDSR:1;
        volatile bool TERI:1;
        volatile bool DDCD:1;
        volatile bool CTS:1;
        volatile bool DSR:1;
        volatile bool RI:1;
        volatile bool DCD:1;
    };
    } MSR;

    volatile unsigned char SCR;

    /*union{
      struct{
        volatile unsigned char DLL;
        volatile unsigned char DLM;
      };
      uint16_t DivisorLatch;
    };*/
  };
  volatile unsigned char RAW[0x0100];
};

static_assert(sizeof(UART_e) == 0x100);

size_t string_length(char const * str) noexcept{
  size_t len = 0;
  for(; *str != '\0'; ++len);
  return len;
}

template<size_t MAX_LEN>
class string{
private:
  char m_data[MAX_LEN] = {0};
  size_t m_current_length = 0;

public:
  string() = default;
  string(const string&) = default;
  string(string&&) = default;
  string(char const* input){
    m_data[0] = '\0';
    for(size_t counter; *input != '\0' and counter < MAX_LEN; ++counter){
      m_data[counter] = input[counter];
    }
  }
  ~string() = default;

  char const& operator[](size_t index) const noexcept{
    return m_data[index];
  }

  char& at(size_t index) {
    if(index >= m_current_length){
      // @FIXME should throw here;
    }

    return m_data[index];
  }

  char const * c_str() const noexcept{
    return m_data;
  }

  size_t size() const noexcept{
    return string_length(m_data);
  }

  char* data() noexcept{
    return m_data;
  }

  char const* data() const noexcept{
    return m_data;
  }

  static size_t get_max_length() noexcept{
    return MAX_LEN;
  }

  void push_back(char c){
    m_data[m_current_length++] = c;
  }
};

template<std::integral INT>
string<16> to_string(INT I){
  string<16> result;
  if constexpr(std::is_signed_v<INT>){
    if(I < 0){
      result.push_back('-');
      I *= -1;
    }
  }

  // here this should be written to a temp, and then reversed for the actual output?

  while(I != 0){
    result.push_back(I % 10 + 0x30);
    I /= 10;
  }

  return result;
}

class UART{
private:
  UART_e& uart;

public:
  UART(UART_e& u)
    : uart(u){
    // throw if u == nullptr
  }

  void print(char c) const{
    uart.t.WRITE = c;
  }

  void print(char const* str) const{
    while(*str != '\0'){
      print(*str);
      ++str;
    }
  }

  template<size_t SIZE>
  void print(string<SIZE> const& str) const{
    print(str.c_str());
  }

  void println(char const* str) const{
    print(str);
    print('\n');
  }

  template<size_t SIZE>
  void println(string<SIZE> const& str) const{
    println(str.c_str());
  }
};

UART_e*const pUART0 = reinterpret_cast<UART_e*>(0x1000'0000);
UART_e& UART0 = *pUART0;

void memcpy(unsigned char* destination, unsigned char* source, size_t length){
  while(length > 0){
    destination[length] = source[length];
    --length;
  }
}

void print_bits(unsigned char c, UART& uart){
  for(size_t i; i < 8; ++i, c = c >> 1){
    uart.print(c & 1 ? '1' : '0');
  }
}

int main(){
  UART u(UART0);
  u.print(temp);

  print_bits(42, u);
  u.print('\n');

  return 0;
}
