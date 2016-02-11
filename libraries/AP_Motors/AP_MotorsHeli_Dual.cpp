// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <AP_HAL/AP_HAL.h>
 
#include "AP_MotorsHeli_Dual.h"

extern const AP_HAL::HAL& hal;

const AP_Param::GroupInfo AP_MotorsHeli_Dual::var_info[] = {
    AP_NESTEDGROUPINFO(AP_MotorsHeli, 0),

    // @Param: SV1_POS
    // @DisplayName: Servo 1 Position
    // @Description: Angular location of swash servo #1
    // @Range: -180 180
    // @Units: Degrees
    // @User: Standard
    // @Increment: 1
    AP_GROUPINFO("SV1_POS", 1, AP_MotorsHeli_Dual, _servo1_pos, AP_MOTORS_HELI_DUAL_SERVO1_POS),

    // @Param: SV2_POS
    // @DisplayName: Servo 2 Position
    // @Description: Angular location of swash servo #2
    // @Range: -180 180
    // @Units: Degrees
    // @User: Standard
    // @Increment: 1
    AP_GROUPINFO("SV2_POS", 2, AP_MotorsHeli_Dual, _servo2_pos,  AP_MOTORS_HELI_DUAL_SERVO2_POS),

    // @Param: SV3_POS
    // @DisplayName: Servo 3 Position
    // @Description: Angular location of swash servo #3
    // @Range: -180 180
    // @Units: Degrees
    // @User: Standard
    // @Increment: 1
    AP_GROUPINFO("SV3_POS", 3, AP_MotorsHeli_Dual, _servo3_pos,  AP_MOTORS_HELI_DUAL_SERVO3_POS),

    // @Param: SV4_POS
    // @DisplayName: Servo 4 Position
    // @Description: Angular location of swash servo #4
    // @Range: -180 180
    // @Units: Degrees
    // @User: Standard
    // @Increment: 1
    AP_GROUPINFO("SV4_POS", 4, AP_MotorsHeli_Dual, _servo4_pos, AP_MOTORS_HELI_DUAL_SERVO4_POS),

    // @Param: SV5_POS
    // @DisplayName: Servo 5 Position
    // @Description: Angular location of swash servo #5
    // @Range: -180 180
    // @Units: Degrees
    // @User: Standard
    // @Increment: 1
    AP_GROUPINFO("SV5_POS", 5, AP_MotorsHeli_Dual, _servo5_pos, AP_MOTORS_HELI_DUAL_SERVO5_POS),

    // @Param: SV6_POS
    // @DisplayName: Servo 6 Position
    // @Description: Angular location of swash servo #6
    // @Range: -180 180
    // @Units: Degrees
    // @User: Standard
    // @Increment: 1
    AP_GROUPINFO("SV6_POS", 6, AP_MotorsHeli_Dual, _servo6_pos, AP_MOTORS_HELI_DUAL_SERVO6_POS),

    // @Param: PHANG1
    // @DisplayName: Swashplate 1 Phase Angle Compensation
    // @Description: Phase angle correction for rotor head.  If pitching the swash forward induces a roll, this can be correct the problem
    // @Range: -90 90
    // @Units: Degrees
    // @User: Advanced
    // @Increment: 1
    AP_GROUPINFO("PHANG1", 7, AP_MotorsHeli_Dual, _swash1_phase_angle, 0),

    // @Param: PHANG2
    // @DisplayName: Swashplate 2 Phase Angle Compensation
    // @Description: Phase angle correction for rotor head.  If pitching the swash forward induces a roll, this can be correct the problem
    // @Range: -90 90
    // @Units: Degrees
    // @User: Advanced
    // @Increment: 1
    AP_GROUPINFO("PHANG2", 8, AP_MotorsHeli_Dual, _swash2_phase_angle, 0),

    // @Param: DUAL_MODE
    // @DisplayName: Dual Mode
    // @Description: Sets the dual mode of the heli, either as tandem or as transverse.
    // @Values: 0:Longitudinal, 1:Transverse
    // @User: Standard
    AP_GROUPINFO("DUAL_MODE", 9, AP_MotorsHeli_Dual, _dual_mode, AP_MOTORS_HELI_DUAL_MODE_TANDEM),

    // @Param: DCP_SCALER
    // @DisplayName: Differential-Collective-Pitch Scaler
    // @Description: Scaling factor applied to the differential-collective-pitch
    // @Range: 0 1
    // @User: Standard
    AP_GROUPINFO("DCP_SCALER", 10, AP_MotorsHeli_Dual, _dcp_scaler, AP_MOTORS_HELI_DUAL_DCP_SCALER),

    // @Param: DCP_YAW
    // @DisplayName: Differential-Collective-Pitch Yaw Mixing
    // @Description: Feed-forward compensation to automatically add yaw input when differential collective pitch is applied.
    // @Range: -10 10
    // @Increment: 0.1
    AP_GROUPINFO("DCP_YAW", 11, AP_MotorsHeli_Dual, _dcp_yaw_effect, 0),

    // @Group: SV1_
    // @Path: ../RC_Channel/RC_Channel.cpp
    AP_SUBGROUPINFO(_swash_servo_1, "SV1_", 12, AP_MotorsHeli_Dual, RC_Channel),

    // @Group: SV2_
    // @Path: ../RC_Channel/RC_Channel.cpp
    AP_SUBGROUPINFO(_swash_servo_2, "SV2_", 13, AP_MotorsHeli_Dual, RC_Channel),

    // @Group: SV3_
    // @Path: ../RC_Channel/RC_Channel.cpp
    AP_SUBGROUPINFO(_swash_servo_3, "SV3_", 14, AP_MotorsHeli_Dual, RC_Channel),

    // @Group: SV4_
    // @Path: ../RC_Channel/RC_Channel.cpp
    AP_SUBGROUPINFO(_swash_servo_4, "SV4_", 15, AP_MotorsHeli_Dual, RC_Channel),

    // @Group: SV5_
    // @Path: ../RC_Channel/RC_Channel.cpp
    AP_SUBGROUPINFO(_swash_servo_5, "SV5_", 16, AP_MotorsHeli_Dual, RC_Channel),

    // @Group: SV6_
    // @Path: ../RC_Channel/RC_Channel.cpp
    AP_SUBGROUPINFO(_swash_servo_6, "SV6_", 17, AP_MotorsHeli_Dual, RC_Channel),

    AP_GROUPEND
};

// set update rate to motors - a value in hertz
void AP_MotorsHeli_Dual::set_update_rate( uint16_t speed_hz )
{
    // record requested speed
    _speed_hz = speed_hz;

    // setup fast channels
    uint32_t mask =
        1U << AP_MOTORS_MOT_1 |
        1U << AP_MOTORS_MOT_2 |
        1U << AP_MOTORS_MOT_3 |
        1U << AP_MOTORS_MOT_4 |
        1U << AP_MOTORS_MOT_5 |
        1U << AP_MOTORS_MOT_6;

    hal.rcout->set_freq(mask, _speed_hz);
}

// enable - starts allowing signals to be sent to motors
void AP_MotorsHeli_Dual::enable()
{
    // enable output channels
    hal.rcout->enable_ch(AP_MOTORS_MOT_1);
    hal.rcout->enable_ch(AP_MOTORS_MOT_2);
    hal.rcout->enable_ch(AP_MOTORS_MOT_3);
    hal.rcout->enable_ch(AP_MOTORS_MOT_4);
    hal.rcout->enable_ch(AP_MOTORS_MOT_5);
    hal.rcout->enable_ch(AP_MOTORS_MOT_6);

    hal.rcout->enable_ch(AP_MOTORS_HELI_DUAL_RSC);

    // disable channels 8 from being used by RC_Channel_aux
    RC_Channel_aux::disable_aux_channel(AP_MOTORS_HELI_DUAL_RSC);
}

// init_outputs
void AP_MotorsHeli_Dual::init_outputs()
{
    // reset swash servo range and endpoints
    reset_swash_servo (_swash_servo_1);
    reset_swash_servo (_swash_servo_2);
    reset_swash_servo (_swash_servo_3);
    reset_swash_servo (_swash_servo_4);
    reset_swash_servo (_swash_servo_5);
    reset_swash_servo (_swash_servo_6);

    // set rotor servo range
    _rotor.init_servo();
}

// output_test - spin a motor at the pwm value specified
//  motor_seq is the motor's sequence number from 1 to the number of motors on the frame
//  pwm value is an actual pwm value that will be output, normally in the range of 1000 ~ 2000
void AP_MotorsHeli_Dual::output_test(uint8_t motor_seq, int16_t pwm)
{
    // exit immediately if not armed
    if (!armed()) {
        return;
    }

    // output to motors and servos
    switch (motor_seq) {
    case 1:
        // swash servo 1
        hal.rcout->write(AP_MOTORS_MOT_1, pwm);
        break;
    case 2:
        // swash servo 2
        hal.rcout->write(AP_MOTORS_MOT_2, pwm);
        break;
    case 3:
        // swash servo 3
        hal.rcout->write(AP_MOTORS_MOT_3, pwm);
        break;
    case 4:
        // swash servo 4
        hal.rcout->write(AP_MOTORS_MOT_4, pwm);
        break;
    case 5:
        // swash servo 5
        hal.rcout->write(AP_MOTORS_MOT_5, pwm);
        break;
    case 6:
        // swash servo 6
        hal.rcout->write(AP_MOTORS_MOT_6, pwm);
        break;
    case 7:
        // main rotor
        hal.rcout->write(AP_MOTORS_HELI_DUAL_RSC, pwm);
        break;
    default:
        // do nothing
        break;
    }
}

// set_desired_rotor_speed
void AP_MotorsHeli_Dual::set_desired_rotor_speed(int16_t desired_speed)
{
    _rotor.set_desired_speed(desired_speed);
}

// calculate_armed_scalars
void AP_MotorsHeli_Dual::calculate_armed_scalars()
{
    _rotor.set_ramp_time(_rsc_ramp_time);
    _rotor.set_runup_time(_rsc_runup_time);
    _rotor.set_critical_speed(_rsc_critical);
    _rotor.set_idle_output(_rsc_idle_output);
    _rotor.set_power_output_range(_rsc_power_low, _rsc_power_high);
    _rotor.recalc_scalers();
}

// calculate_scalars
void AP_MotorsHeli_Dual::calculate_scalars()
{    // range check collective min, max and mid
    if( _collective_min >= _collective_max ) {
        _collective_min = AP_MOTORS_HELI_COLLECTIVE_MIN;
        _collective_max = AP_MOTORS_HELI_COLLECTIVE_MAX;
    }
    _collective_mid = constrain_int16(_collective_mid, _collective_min, _collective_max);

    // calculate collective mid point as a number from 0 to 1000
    _collective_mid_pwm = ((float)(_collective_mid-_collective_min))/((float)(_collective_max-_collective_min))*1000.0f;

    // calculate maximum collective pitch range from full positive pitch to zero pitch
    _collective_range = 1000 - _collective_mid_pwm;

    // determine roll, pitch and collective input scaling
    _roll_scaler = (float)_cyclic_max/4500.0f;
    _pitch_scaler = (float)_cyclic_max/4500.0f;
    _yaw_scaler = (float)_cyclic_max/4500.0f;
    _collective_scalar = ((float)(_collective_max-_collective_min))/1000.0f;

    // calculate factors based on swash type and servo position
    calculate_roll_pitch_collective_factors();

    // set mode of main rotor controller and trigger recalculation of scalars
    _rotor.set_control_mode(static_cast<RotorControlMode>(_rsc_mode.get()));
    calculate_armed_scalars();
}

// calculate_swash_factors - calculate factors based on swash type and servo position
void AP_MotorsHeli_Dual::calculate_roll_pitch_collective_factors()
{
    if (_dual_mode == AP_MOTORS_HELI_DUAL_MODE_TRANSVERSE) {
        // roll factors
        _rollFactor[CH_1] = _dcp_scaler;
        _rollFactor[CH_2] = _dcp_scaler;
        _rollFactor[CH_3] = _dcp_scaler;

        _rollFactor[CH_4] = -_dcp_scaler;
        _rollFactor[CH_5] = -_dcp_scaler;
        _rollFactor[CH_6] = -_dcp_scaler;

        // pitch factors
        _pitchFactor[CH_1] = cosf(radians(_servo1_pos - (_swash1_phase_angle + _delta_phase_angle)));
        _pitchFactor[CH_2] = cosf(radians(_servo2_pos - (_swash1_phase_angle + _delta_phase_angle)));
        _pitchFactor[CH_3] = cosf(radians(_servo3_pos - (_swash1_phase_angle + _delta_phase_angle)));

        _pitchFactor[CH_4] = cosf(radians(_servo4_pos - (_swash2_phase_angle + _delta_phase_angle)));
        _pitchFactor[CH_5] = cosf(radians(_servo5_pos - (_swash2_phase_angle + _delta_phase_angle)));
        _pitchFactor[CH_6] = cosf(radians(_servo6_pos - (_swash2_phase_angle + _delta_phase_angle)));

        // yaw factors
        _yawFactor[CH_1] = cosf(radians(_servo1_pos + 180 - (_swash1_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_2] = cosf(radians(_servo2_pos + 180 - (_swash1_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_3] = cosf(radians(_servo3_pos + 180 - (_swash1_phase_angle + _delta_phase_angle)));

        _yawFactor[CH_4] = cosf(radians(_servo4_pos - (_swash2_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_5] = cosf(radians(_servo5_pos - (_swash2_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_6] = cosf(radians(_servo6_pos - (_swash2_phase_angle + _delta_phase_angle)));
    } else { // AP_MOTORS_HELI_DUAL_MODE_TANDEM
        // roll factors
        _rollFactor[CH_1] = cosf(radians(_servo1_pos + 90 - (_swash1_phase_angle + _delta_phase_angle)));
        _rollFactor[CH_2] = cosf(radians(_servo2_pos + 90 - (_swash1_phase_angle + _delta_phase_angle)));
        _rollFactor[CH_3] = cosf(radians(_servo3_pos + 90 - (_swash1_phase_angle + _delta_phase_angle)));

        _rollFactor[CH_4] = cosf(radians(_servo4_pos + 90 - (_swash2_phase_angle + _delta_phase_angle)));
        _rollFactor[CH_5] = cosf(radians(_servo5_pos + 90 - (_swash2_phase_angle + _delta_phase_angle)));
        _rollFactor[CH_6] = cosf(radians(_servo6_pos + 90 - (_swash2_phase_angle + _delta_phase_angle)));

        // pitch factors
        _pitchFactor[CH_1] = _dcp_scaler;
        _pitchFactor[CH_2] = _dcp_scaler;
        _pitchFactor[CH_3] = _dcp_scaler;

        _pitchFactor[CH_4] = -_dcp_scaler;
        _pitchFactor[CH_5] = -_dcp_scaler;
        _pitchFactor[CH_6] = -_dcp_scaler;

        // yaw factors
        _yawFactor[CH_1] = cosf(radians(_servo1_pos + 90 - (_swash1_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_2] = cosf(radians(_servo2_pos + 90 - (_swash1_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_3] = cosf(radians(_servo3_pos + 90 - (_swash1_phase_angle + _delta_phase_angle)));

        _yawFactor[CH_4] = cosf(radians(_servo4_pos + 270 - (_swash2_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_5] = cosf(radians(_servo5_pos + 270 - (_swash2_phase_angle + _delta_phase_angle)));
        _yawFactor[CH_6] = cosf(radians(_servo6_pos + 270 - (_swash2_phase_angle + _delta_phase_angle)));
    }

    // collective factors
    _collectiveFactor[CH_1] = 1;
    _collectiveFactor[CH_2] = 1;
    _collectiveFactor[CH_3] = 1;

    _collectiveFactor[CH_4] = 1;
    _collectiveFactor[CH_5] = 1;
    _collectiveFactor[CH_6] = 1;
}

// get_motor_mask - returns a bitmask of which outputs are being used for motors or servos (1 means being used)
//  this can be used to ensure other pwm outputs (i.e. for servos) do not conflict
uint16_t AP_MotorsHeli_Dual::get_motor_mask()
{
    // dual heli uses channels 1,2,3,4,5,6 and 8
    return (1U << 0 | 1U << 1 | 1U << 2 | 1U << 3 | 1U << 4 | 1U << 5 | 1U << 6 | 1U << AP_MOTORS_HELI_DUAL_RSC);
}

// update_motor_controls - sends commands to motor controllers
void AP_MotorsHeli_Dual::update_motor_control(RotorControlState state)
{
    // Send state update to motors
    _rotor.output(state);

    // Check if rotors are run-up
    _heliflags.rotor_runup_complete = _rotor.is_runup_complete();
}

// set_delta_phase_angle for setting variable phase angle compensation and force
// recalculation of collective factors
void AP_MotorsHeli_Dual::set_delta_phase_angle(int16_t angle)
{
    angle = constrain_int16(angle, -90, 90);
    _delta_phase_angle = angle;
    calculate_roll_pitch_collective_factors();
}

//
// move_actuators - moves swash plate to attitude of parameters passed in
//                - expected ranges:
//                       roll : -4500 ~ 4500
//                       pitch: -4500 ~ 4500
//                       collective: 0 ~ 1000
//                       yaw:   -4500 ~ 4500
//
void AP_MotorsHeli_Dual::move_actuators(int16_t roll_out, int16_t pitch_out, int16_t collective_in, int16_t yaw_out)
{    
    int16_t collective_out_scaled;
    int16_t yaw_compensation;

    // initialize limits flag
    limit.roll_pitch = false;
    limit.yaw = false;
    limit.throttle_lower = false;
    limit.throttle_upper = false;

    // rescale roll_out and pitch-out into the min and max ranges to provide linear motion
    // across the input range instead of stopping when the input hits the constrain value
    // these calculations are based on an assumption of the user specified roll_max and pitch_max
    // coming into this equation at 4500 or less, and based on the original assumption of the
    // total _servo_x.servo_out range being -4500 to 4500.
    roll_out = roll_out * _roll_scaler;
    if (roll_out < -_cyclic_max) {
        roll_out = -_cyclic_max;
        limit.roll_pitch = true;
    }
    if (roll_out > _cyclic_max) {
        roll_out = _cyclic_max;
        limit.roll_pitch = true;
    }

    // scale pitch and update limits
    pitch_out = pitch_out * _pitch_scaler;
    if (pitch_out < -_cyclic_max) {
        pitch_out = -_cyclic_max;
        limit.roll_pitch = true;
    }
    if (pitch_out > _cyclic_max) {
        pitch_out = _cyclic_max;
        limit.roll_pitch = true;
    }
    
    // if servo output not in manual mode, process pre-compensation factors
    if (_servo_mode == SERVO_CONTROL_MODE_AUTOMATED) {
        // add differential collective pitch yaw compensation
        if (_dual_mode == AP_MOTORS_HELI_DUAL_MODE_TRANSVERSE) {
            yaw_compensation = _dcp_yaw_effect * roll_out;
        } else { // AP_MOTORS_HELI_DUAL_MODE_TANDEM
            yaw_compensation = _dcp_yaw_effect * pitch_out;
        }
        yaw_out = yaw_out + yaw_compensation;
    }

    // scale yaw and update limits
    yaw_out = yaw_out * _yaw_scaler;
    if (yaw_out < -_cyclic_max) {
        yaw_out = -_cyclic_max;
        limit.yaw = true;
    }
    if (yaw_out > _cyclic_max) {
        yaw_out = _cyclic_max;
        limit.yaw = true;
    }

    // constrain collective input
    _collective_out = collective_in;
    if (_collective_out <= 0) {
        _collective_out = 0;
        limit.throttle_lower = true;
    }
    if (_collective_out >= 1000) {
        _collective_out = 1000;
        limit.throttle_upper = true;
    }

    // ensure not below landed/landing collective
    if (_heliflags.landing_collective && _collective_out < _land_collective_min) {
        _collective_out = _land_collective_min;
        limit.throttle_lower = true;
    }

    // scale collective pitch
    collective_out_scaled = _collective_out * _collective_scalar + _collective_min - 1000;

    // feed power estimate into main rotor controller
    // ToDo: add main rotor cyclic power?
    _main_rotor_power = ((float)(abs(_collective_out - _collective_mid_pwm)) / _collective_range);
    _rotor.set_motor_load(_main_rotor_power);

    // swashplate servos
    _swash_servo_1.servo_out = (_rollFactor[CH_1] * roll_out + _pitchFactor[CH_1] * pitch_out + _yawFactor[CH_1] * yaw_out)/10 + _collectiveFactor[CH_1] * collective_out_scaled + (_swash_servo_1.radio_trim-1500);
    _swash_servo_2.servo_out = (_rollFactor[CH_2] * roll_out + _pitchFactor[CH_2] * pitch_out + _yawFactor[CH_2] * yaw_out)/10 + _collectiveFactor[CH_2] * collective_out_scaled + (_swash_servo_2.radio_trim-1500);
    _swash_servo_3.servo_out = (_rollFactor[CH_3] * roll_out + _pitchFactor[CH_3] * pitch_out + _yawFactor[CH_3] * yaw_out)/10 + _collectiveFactor[CH_3] * collective_out_scaled + (_swash_servo_3.radio_trim-1500);
    _swash_servo_4.servo_out = (_rollFactor[CH_4] * roll_out + _pitchFactor[CH_4] * pitch_out + _yawFactor[CH_4] * yaw_out)/10 + _collectiveFactor[CH_4] * collective_out_scaled + (_swash_servo_4.radio_trim-1500);
    _swash_servo_5.servo_out = (_rollFactor[CH_5] * roll_out + _pitchFactor[CH_5] * pitch_out + _yawFactor[CH_5] * yaw_out)/10 + _collectiveFactor[CH_5] * collective_out_scaled + (_swash_servo_5.radio_trim-1500);
    _swash_servo_6.servo_out = (_rollFactor[CH_6] * roll_out + _pitchFactor[CH_6] * pitch_out + _yawFactor[CH_6] * yaw_out)/10 + _collectiveFactor[CH_6] * collective_out_scaled + (_swash_servo_6.radio_trim-1500);

    // use servo_out to calculate pwm_out and radio_out
    _swash_servo_1.calc_pwm();
    _swash_servo_2.calc_pwm();
    _swash_servo_3.calc_pwm();
    _swash_servo_4.calc_pwm();
    _swash_servo_5.calc_pwm();
    _swash_servo_6.calc_pwm();

    // actually move the servos
    hal.rcout->cork();

    hal.rcout->write(AP_MOTORS_MOT_1, _swash_servo_1.radio_out);
    hal.rcout->write(AP_MOTORS_MOT_2, _swash_servo_2.radio_out);
    hal.rcout->write(AP_MOTORS_MOT_3, _swash_servo_3.radio_out);
    hal.rcout->write(AP_MOTORS_MOT_4, _swash_servo_4.radio_out);
    hal.rcout->write(AP_MOTORS_MOT_5, _swash_servo_5.radio_out);
    hal.rcout->write(AP_MOTORS_MOT_6, _swash_servo_6.radio_out);
    
    hal.rcout->push();
}


// servo_test - move servos through full range of movement
void AP_MotorsHeli_Dual::servo_test()
{
    // this test cycle is equivalent to that of AP_MotorsHeli_Single, but excluding
    // mixing of yaw, as that physical movement is represented by pitch and roll

    _servo_test_cycle_time += 1.0f / _loop_rate;

    if ((_servo_test_cycle_time >= 0.0f && _servo_test_cycle_time < 0.5f)||                                   // Tilt swash back
        (_servo_test_cycle_time >= 6.0f && _servo_test_cycle_time < 6.5f)){
        _pitch_test += (4500 / (_loop_rate/2));
        _oscillate_angle += 8 * M_PI_F / _loop_rate;
    } else if ((_servo_test_cycle_time >= 0.5f && _servo_test_cycle_time < 4.5f)||                            // Roll swash around
               (_servo_test_cycle_time >= 6.5f && _servo_test_cycle_time < 10.5f)){
        _oscillate_angle += M_PI_F / (2 * _loop_rate);
        _roll_test = 4500 * sinf(_oscillate_angle);
        _pitch_test = 4500 * cosf(_oscillate_angle);
    } else if ((_servo_test_cycle_time >= 4.5f && _servo_test_cycle_time < 5.0f)||                            // Return swash to level
               (_servo_test_cycle_time >= 10.5f && _servo_test_cycle_time < 11.0f)){
        _pitch_test -= (4500 / (_loop_rate/2));
        _oscillate_angle += 8 * M_PI_F / _loop_rate;
    } else if (_servo_test_cycle_time >= 5.0f && _servo_test_cycle_time < 6.0f){                              // Raise swash to top
        _collective_test += (1000 / _loop_rate);
        _oscillate_angle += 2 * M_PI_F / _loop_rate;
    } else if (_servo_test_cycle_time >= 11.0f && _servo_test_cycle_time < 12.0f){                            // Lower swash to bottom
        _collective_test -= (1000 / _loop_rate);
        _oscillate_angle += 2 * M_PI_F / _loop_rate;
    } else {                                                                                                  // reset cycle
        _servo_test_cycle_time = 0.0f;
        _oscillate_angle = 0.0f;
        _collective_test = 0.0f;
        _roll_test = 0.0f;
        _pitch_test = 0.0f;
        // decrement servo test cycle counter at the end of the cycle
        if (_servo_test_cycle_counter > 0){
            _servo_test_cycle_counter--;
        }
    }

    // over-ride servo commands to move servos through defined ranges
    _throttle_control_input = _collective_test;
    _roll_control_input = _roll_test;
    _pitch_control_input = _pitch_test;
}
