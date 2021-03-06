//#include <chrono>
#include "your_stuff.h"
#include "can_common.h"

#include <thread>
#include <iostream>



void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    switch (_frame->can_id) {
        case CAN::MSG::USERIN_ID: {
            const struct CAN::MSG::_userin *d = reinterpret_cast<const struct CAN::MSG::_userin * >((_frame->data));
            //this->InstrumentCluster.ignite(d->IGNT);
            //printUserIn(d);
            std::string str = "Acc pos: " + std::to_string(d->accelerator_pedal)+ "%\n"+
                              "Brk pos: " + std::to_string(d->brake_pedal) + "%";
            // QString qstr = QString::fromStdString(str);
            this->InstrumentCluster.setTXT(str.c_str());
        }
        break;
        case CAN::MSG::DRIVETRAIN_ID: {
            const struct CAN::MSG::_drivetrain *d = reinterpret_cast<const struct CAN::MSG::_drivetrain * >((_frame->data));
            this->InstrumentCluster.ignite(d->engine_status);
            this->InstrumentCluster.setRPM(d->engine_rpm * 37);
            this->InstrumentCluster.setSpeed(d->vehicle_speed);
            this->InstrumentCluster.setGearPindle_int(d->gear_lever_position);
            this->InstrumentCluster.setGear(d->gear_number);
            if(d->engine_status == 1){
                this->InstrumentCluster.setFuelGauges(160);
                this->InstrumentCluster.setOilTemperatureGauges(120);
                this->InstrumentCluster.setTemperatureGauges(145);
            }
            else{
                this->InstrumentCluster.setFuelGauges(0);
                this->InstrumentCluster.setOilTemperatureGauges(0);
                this->InstrumentCluster.setTemperatureGauges(0);
            }
        }
        break;
/*     case CAN::MSG::GAUGES_ID: {
        const struct CAN::MSG::Gauges_t::_inner* s =
                reinterpret_cast<const struct CAN::MSG::Gauges_t::_inner* >((_frame->data));
        this->InstrumentCluster.setFuelGauges(s->G_FUEL);
        this->InstrumentCluster.setTemperatureGauges(s->G_TEMP);
        this->InstrumentCluster.setOilTemperatureGauges(s->G_OILT);
        break;
    } */
    case CAN::MSG::ICONSS_ID:
        struct _icons  p; //= reinterpret_cast<struct _icons * >((_frame->data));
        static bool once = false;

        if (!once) {
            p.hazard = 1;
            once = true;
        } else
            p.hazard = 0;
        this->InstrumentCluster.setIcon(&p);
        break;
/*     case CAN::MSG::GEARBX_ID: {
        const struct CAN::MSG::Gearbx_t::_bits *d = reinterpret_cast<const struct CAN::MSG::Gearbx_t::_bits * >((_frame->data));
        this->InstrumentCluster.setGearPindle_int(d->GEAR_P);
        this->InstrumentCluster.setGear(d->GEAR_N);
    }

        break;
    case CAN::MSG::ENGINE_ID: {
        const struct CAN::MSG::_engine *d = reinterpret_cast<const struct CAN::MSG::_drivetrain * >((_frame->data));
        this->InstrumentCluster.ignite(d->RUN);
        this->InstrumentCluster.setRPM(d->RPM);
        this->InstrumentCluster.setSpeed(d->SPD);

    }
        */
        break;
    default:
        break;
    }

}















/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();
    this->InstrumentCluster.init(_vs);
    this->startTimer(1);
}

bool yourStuff::run() {
    bool ret = true;
    CANOpener::ReadStatus status = CANOpener::ReadStatus::OK;


        canfd_frame frame;
        this->CANReader.read(&frame);
        /*while*/if (status == CANOpener::ReadStatus::OK) {
        this->YouHaveJustRecievedACANFrame(&frame);
    }
    if (status == CANOpener::ReadStatus::ERROR) ret = false;
    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) this->Counter++;
    else   this->Counter = 0;
    //if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
    exit(-1);
    }

}

