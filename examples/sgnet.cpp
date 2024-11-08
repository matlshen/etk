#include "etk/active_object.h"
#include <cstdint>
#include <iostream>

class can_frame {
  public:
    can_frame() = default;
    
    enum id_type : uint8_t { STANDARD, EXTENDED };

    enum rtr_type : uint8_t { DATA, REMOTE };

    can_frame(uint32_t id, id_type id_type, rtr_type rtr_type)
        : id(id), id_type(id_type), rtr_type(rtr_type) {}

    uint32_t id;
    id_type id_type;
    rtr_type rtr_type;
    uint8_t dlc;
    uint8_t __pad;
    uint8_t data[8];
};

class fake_can_driver {
public:
    fake_can_driver() = default;

    enum error_type : uint8_t { NONE, BUS_OFF, BUS_ERROR };

    error_type send(const can_frame& frame) {
        std::cout << "sending 0x" << std::hex << frame.id << std::endl;
        return error_type::NONE;
    }
};


class tx_ao : public etk::active_object<1024, can_frame, 3> {
public:
    bool process(can_frame& msg) {

        std::cout << "sending 0x" << std::hex << msg.id << std::endl;


        static int counter = 0;
        if (counter++ == 2) {
            return false;
        }
        else {
            return true;
        }
    }
};

int main() {
    tx_ao ao;

    ao.send({0x123, can_frame::STANDARD, can_frame::DATA});
    ao.send({0x123, can_frame::STANDARD, can_frame::DATA});
    ao.send({0x123, can_frame::STANDARD, can_frame::DATA});

    ao.join();
    return 0;
}