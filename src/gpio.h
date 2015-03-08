#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include <string>
#include <fstream>
#include <iostream>

//arietta ACMEsystems
#define KERNEL_ID_64    "C0"
#define KERNEL_ID_65    "C1"
#define KERNEL_ID_66    "C2"
#define KERNEL_ID_67    "C3"
#define KERNEL_ID_68    "C4"
#define KERNEL_ID_92    "C28"
#define KERNEL_ID_6    "A6"
#define KERNEL_ID_8    "A8"
#define KERNEL_ID_0    "A0"
#define KERNEL_ID_29    "A29"
#define KERNEL_ID_28    "A28"
#define KERNEL_ID_27    "A27"
#define KERNEL_ID_26    "A26"
#define KERNEL_ID_25    "A25"
#define KERNEL_ID_24    "A24"
#define KERNEL_ID_23    "A23"
#define KERNEL_ID_22    "A22"
#define KERNEL_ID_21    "A21"
#define KERNEL_ID_31    "A31"
#define KERNEL_ID_30    "A30"
#define KERNEL_ID_1    "A1"
#define KERNEL_ID_7    "A7"
#define KERNEL_ID_5    "A5"
#define KERNEL_ID_91    "C27"
#define KERNEL_ID_95    "C31"
#define KERNEL_ID_43    "B11"
#define KERNEL_ID_44    "B12"
#define KERNEL_ID_45    "B13"
#define KERNEL_ID_46    "B14"
#define KERNEL_ID_81    "C17"   //onboard button

enum GPIODirection {
    GPIO_IN  = 0,
    GPIO_OUT = 1
};

enum GPIOValue {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
};

class GPIO {
    public:
        explicit GPIO(int id);
        ~GPIO();

        int  GetValue();
        void SetValue(int value);
        int  GetActiveLow();
        void SetActiveLow(int value);
        int  GetDirection();
        void SetDirection(int value);

    private:
        int id_;

        std::fstream value_stream_;
        std::fstream active_low_stream_;
        std::fstream direction_stream_;

        bool Exists();
        void Export();
        void Unexport();

        static const std::string PATH_EXPORT;
        static const std::string PATH_UNEXPORT;
        static const std::string PREFIX;
        static const std::string POSTFIX_VALUE;
        static const std::string POSTFIX_ACTIVE_LOW;
        static const std::string POSTFIX_DIRECTION;
};

#endif
