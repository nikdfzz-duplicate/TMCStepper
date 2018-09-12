#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC5130Stepper::TMC5130Stepper(uint16_t pinCS, float RS) : TMC2130Stepper(pinCS, RS) {}
TMC5130Stepper::TMC5130Stepper(uint16_t pinCS) : TMC2130Stepper(pinCS, 0.15) {}

void TMC5130Stepper::begin() {
  //set pins
  pinMode(_pinCS, OUTPUT);
  switchCSpin(HIGH);

  if (uses_sw_spi) TMC_SW_SPI.init();

  GCONF(GCONF_register.sr);
  CHOPCONF(CHOPCONF_register.sr);
  COOLCONF(COOLCONF_register.sr);
  PWMCONF(PWMCONF_register.sr);
  IHOLD_IRUN(IHOLD_IRUN_register.sr);

  toff(8); //off_time(8);
  tbl(1); //blank_time(24);

  XTARGET(0);
  XACTUAL(0);
  //while (( RAMP_STAT() & cfg.VZERO_bm) != cfg.VZERO_bm) {}

  _started = true;
}

///////////////////////////////////////////////////////////////////////////////////////
// R: IFCNT
uint8_t TMC5130Stepper::IFCNT() { return read(IFCNT_address); }
///////////////////////////////////////////////////////////////////////////////////////
// W: SLAVECONF
uint16_t TMC5130Stepper::SLAVECONF() { return SLAVECONF_register.sr; }
void TMC5130Stepper::SLAVECONF(uint16_t input) {
  SLAVECONF_register.sr = input;
  write(SLAVECONF_address, SLAVECONF_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
uint32_t  TMC5130Stepper::IOIN() {
  IOIN_register.sr = read(IOIN_address);
  return IOIN_register.sr;
}
bool    TMC5130Stepper::refl_step()      { IOIN(); return IOIN_register.refl_step; }
bool    TMC5130Stepper::refr_dir()       { IOIN(); return IOIN_register.refr_dir; }
bool    TMC5130Stepper::encb_dcen_cfg4() { IOIN(); return IOIN_register.encb_dcen_cfg4; }
bool    TMC5130Stepper::enca_dcin_cfg5() { IOIN(); return IOIN_register.enca_dcin_cfg5; }
bool    TMC5130Stepper::drv_enn_cfg6()   { IOIN(); return IOIN_register.drv_enn_cfg6; }
bool    TMC5130Stepper::enc_n_dco()      { IOIN(); return IOIN_register.enc_n_dco; }
bool    TMC5130Stepper::sd_mode()        { IOIN(); return IOIN_register.sd_mode; }
bool    TMC5130Stepper::swcomp_in()      { IOIN(); return IOIN_register.swcomp_in; }
uint8_t   TMC5130Stepper::version()      { IOIN(); return IOIN_register.version; }
///////////////////////////////////////////////////////////////////////////////////////
// W: OUTPUT
bool TMC5130Stepper::TMC_OUTPUT() { return OUTPUT_register.sr; }
void TMC5130Stepper::TMC_OUTPUT(bool input) {
  OUTPUT_register.sr = input;
  write(OUTPUT_address, OUTPUT_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: X_COMPARE
uint32_t TMC5130Stepper::X_COMPARE() { return X_COMPARE_register.sr; }
void TMC5130Stepper::X_COMPARE(uint32_t input) {
  X_COMPARE_register.sr = input;
  write(X_COMPARE_address, X_COMPARE_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: RAMPMODE
uint8_t TMC5130Stepper::RAMPMODE() { return read(RAMPMODE_address); }
void TMC5130Stepper::RAMPMODE(uint8_t input) {
  RAMPMODE_register.sr = input;
  write(THIGH_address, THIGH_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XACTUAL
int32_t TMC5130Stepper::XACTUAL() { return read(XACTUAL_address); }
void TMC5130Stepper::XACTUAL(int32_t input) {
  write(XACTUAL_address, input);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: VACTUAL
int32_t TMC5130Stepper::VACTUAL() { return read(VACTUAL_address); }
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTART
uint32_t TMC5130Stepper::VSTART() { return VSTART_register.sr; }
void TMC5130Stepper::VSTART(uint32_t input) {
  VSTART_register.sr = input;
  write(VSTART_address, VSTART_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: A1
uint16_t TMC5130Stepper::A1() { return A1_register.sr; }
void TMC5130Stepper::A1(uint16_t input) {
  A1_register.sr = input;
  write(A1_address, A1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: V1
uint32_t TMC5130Stepper::V1() { return V1_register.sr; }
void TMC5130Stepper::V1(uint32_t input) {
  V1_register.sr = input;
  write(V1_address, V1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: AMAX
uint16_t TMC5130Stepper::AMAX() { return AMAX_register.sr; }
void TMC5130Stepper::AMAX(uint16_t input) {
  AMAX_register.sr = input;
  write(AMAX_address, AMAX_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VMAX
uint32_t TMC5130Stepper::VMAX() { return VMAX_register.sr; }
void TMC5130Stepper::VMAX(uint32_t input) {
  VMAX_register.sr = input;
  write(VMAX_address, VMAX_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: DMAX
uint16_t TMC5130Stepper::DMAX() { return DMAX_register.sr; }
void TMC5130Stepper::DMAX(uint16_t input) {
  DMAX_register.sr = input;
  write(DMAX_address, DMAX_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: D1
uint16_t TMC5130Stepper::D1() { return D1_register.sr; }
void TMC5130Stepper::D1(uint16_t input) {
  D1_register.sr = input;
  write(D1_address, D1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTOP
uint32_t TMC5130Stepper::VSTOP() { return VSTOP_register.sr; }
void TMC5130Stepper::VSTOP(uint32_t input) {
  if (input == 0 && RAMPMODE() == 0) return;
  VSTOP_register.sr = input;
  write(VSTOP_address, VSTOP_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TZEROWAIT
uint16_t TMC5130Stepper::TZEROWAIT() { return TZEROWAIT_register.sr; }
void TMC5130Stepper::TZEROWAIT(uint16_t input) {
  TZEROWAIT_register.sr = input;
  write(TZEROWAIT_address, TZEROWAIT_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XTARGET
int32_t TMC5130Stepper::XTARGET() { return read(XTARGET_address); }
void TMC5130Stepper::XTARGET(int32_t input) {
  write(XTARGET_address, input);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: XLATCH
uint32_t TMC5130Stepper::XLATCH() { return read(XLATCH_address); }
///////////////////////////////////////////////////////////////////////////////////////
// RW: X_ENC
int32_t TMC5130Stepper::X_ENC() { return read(X_ENC_address); }
void TMC5130Stepper::X_ENC(int32_t input) {
  write(X_ENC_address, input);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: ENC_CONST
uint16_t TMC5130Stepper::ENC_CONST() { return ENC_CONST_register.sr; }
void TMC5130Stepper::ENC_CONST(uint16_t input) {
  ENC_CONST_register.sr = input;
  write(ENC_CONST_address, ENC_CONST_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: ENC_STATUS
bool TMC5130Stepper::ENC_STATUS() { return read(ENC_STATUS_address); }
///////////////////////////////////////////////////////////////////////////////////////
// R: ENC_LATCH
uint32_t TMC5130Stepper::ENC_LATCH() { return read(ENC_LATCH_address); }
