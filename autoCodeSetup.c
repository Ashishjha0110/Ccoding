void ladder(void){
  ST_PLC_ClrOne_DO(DI_Channel_I1_0)
  ST_PLC_SetOne_DO(DI_Channel_I0_0)
  ST_PLC_SetOne_DO(DI_Channel_I0_0)
  ST_PLC_SetOne_DO(DI_Channel_I0_0)
  ST_PLC_SetOne_DO(DI_Channel_I0_0)
  ST_PLC_ClrOne_DO(DI_Channel_I1_0)
  ST_PLC_ClrOne_DO(DI_Channel_I1_0)
  ST_PLC_ClrOne_DO(DI_Channel_I1_0)
}
