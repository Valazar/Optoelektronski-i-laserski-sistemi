#include "color16.h"

I2C_HandleTypeDef hi2c2;

uint8_t COLOR16_init(I2C_HandleTypeDef i2c_handle)
{
	hi2c2=i2c_handle;

	if(HAL_I2C_IsDeviceReady(&hi2c2,COLOR16_DEVICE_ADDRESS<<1, 5, 100) == HAL_OK )
		return 1;
	else
		return 0;
}



void color16_write_register(uint8_t reg, uint8_t data_in) {

    uint8_t data_buf[2] = {0};

    // Form the data buffer
    data_buf[0] = reg;
    data_buf[1] = data_in;

    // Write the register via I2C
    HAL_I2C_Master_Transmit(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, (uint8_t *)data_buf, 2, 1000);


}

void color16_read_register(uint8_t reg, uint8_t *data_out) {

    // Write the register address to the device
    HAL_I2C_Master_Transmit(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, &reg, 1, 1000);

    // Read data from the device
    HAL_I2C_Master_Receive(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, data_out, 1, 1000);
}


void color16_write_register_word(uint8_t reg, uint16_t data_in) {

    uint8_t data_buf[3] = {0};

    // Form the data buffer
    data_buf[0] = reg;
    data_buf[1] = (uint8_t)(data_in & 0xFF);
    data_buf[2] = (uint8_t)((data_in >> 8) & 0xFF);

    // Write the register via I2C
    HAL_I2C_Master_Transmit(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, (uint8_t *)data_buf, 3, 1000);


}

void color16_read_register_word(uint8_t reg, uint16_t *data_out) {

    uint8_t data_buf[2] = {0};

    // Send the register address
    HAL_I2C_Master_Transmit(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, &reg, 1, 1000);

    // Read data from the device
    HAL_I2C_Master_Receive(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, data_buf, 2, 1000);

    // Combine the received bytes into a 16-bit value
    *data_out = ((uint16_t)data_buf[1] << 8) | data_buf[0];

}

void enable_register(void){

	color16_write_register(COLOR16_REG_ENABLE, 0x01);

}

void measure_enable(void){

	color16_write_register(COLOR16_REG_ENABLE, 0x03);

}

void sp_th_configure (void) {

	color16_write_register(COLOR16_REG_SP_TH_L_LSB, 0x10);
	GUI_Delay(100);
	color16_write_register(COLOR16_REG_SP_TH_L_MSB, 0x01);
	//GUI_Delay(100);
	//color16_write_register(COLOR16_REG_SP_TH_H_LSB, 0x40);
	//GUI_Delay(100);
	//color16_write_register(COLOR16_REG_SP_TH_H_MSB, 0x9C);

}
//HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
//HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)

void color16_generic_read(uint8_t reg, uint8_t *data_out, uint8_t len) {

    // Transmit register address
    HAL_I2C_Mem_Write(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, reg, 1, NULL, 0, 1000);

    // Receive data
    HAL_I2C_Mem_Read(&hi2c2, COLOR16_DEVICE_ADDRESS << 1, reg, 1, data_out, len, 1000);


}

//PODESAVANJE REG BANKE Register Bank Access
//0: Register access to register 0x80 and above
//1: Register access to register 0x20 to 0x7F
void color16_set_reg_bank_access ( uint8_t reg_bank )
{
    uint8_t cfg_0;
    color16_read_register ( COLOR16_REG_CFG_0, &cfg_0 );

    if ( reg_bank && ( COLOR16_CFG_0_REG_BANK != ( cfg_0 & COLOR16_CFG_0_REG_BANK ) ) )
    {
        cfg_0 |= COLOR16_CFG_0_REG_BANK;
        color16_write_register ( COLOR16_REG_CFG_0, cfg_0 );
    }
    if ( !reg_bank && ( COLOR16_CFG_0_REG_BANK == ( cfg_0 & COLOR16_CFG_0_REG_BANK ) ) )
    {
        cfg_0 &= ~COLOR16_CFG_0_REG_BANK;
        color16_write_register ( COLOR16_REG_CFG_0, cfg_0 );
    }

}

void color16_set_integration_time_ms(float int_time_ms )
{
    if ( ( int_time_ms > COLOR16_INTEGRATION_TIME_MIN ) && ( int_time_ms < COLOR16_INTEGRATION_TIME_MAX ) )
    {

    	uint16_t astep = 0;
    	uint16_t atime = 0;
    	for ( uint16_t cnt = 0; cnt <= COLOR16_ATIME_MAX; cnt++ )
    	{
        	if ( ( int_time_ms / ( cnt + 1 ) ) < ( ( COLOR16_ASTEP_MAX + 1 ) * COLOR16_SINGLE_STEP_MS ) )
        	{
            	atime = cnt;
            	astep = ( uint16_t ) ( int_time_ms / ( ( atime + 1 ) * COLOR16_SINGLE_STEP_MS ) );
            	break;
        	}
    	}
    	color16_write_register ( COLOR16_REG_ATIME, ( uint8_t ) ( atime & 0xFF ) );
    	color16_write_register_word ( COLOR16_REG_ASTEP_LSB, astep ) ;
	}

}

void color16_set_wait_time_ms(float wait_time_ms )
{
    if ( ( wait_time_ms > COLOR16_WAIT_TIME_MIN ) && ( wait_time_ms < COLOR16_WAIT_TIME_MAX ) )
    {
        uint16_t wtime = ( wait_time_ms / COLOR16_WAIT_STEP_MS );
    	if ( wtime )
    	{
        	wtime--;
    	}
    	color16_write_register ( COLOR16_REG_WTIME, ( uint8_t ) ( wtime & 0xFF ) );
    }
}

void color16_default_cfg ( void )
{
	color16_set_reg_bank_access (COLOR16_ACCESS_REG_BANK_20H_7FH );

    color16_set_reg_bank_access (COLOR16_ACCESS_REG_BANK_ABOVE_80H );

    color16_write_register (COLOR16_REG_ENABLE, COLOR16_ENABLE_POFF );
    GUI_Delay(100);
    color16_write_register (COLOR16_REG_ENABLE, COLOR16_ENABLE_PON );
    GUI_Delay(100);
    color16_write_register (COLOR16_REG_CONTROL, COLOR16_CONTROL_SW_RESET );
    GUI_Delay(100);
    //color16_enable_ext_led ( ctx, COLOR16_LED_DRIVE_CURR_DEFAULT );

    color16_set_integration_time_ms (COLOR16_INTEGRATION_TIME_DEFAULT );

    color16_set_wait_time_ms (COLOR16_WAIT_TIME_DEFAULT );

    color16_write_register (COLOR16_REG_CFG_1, COLOR16_CFG_1_AGAIN_4 );

    color16_write_register (COLOR16_REG_CFG_20, COLOR16_CFG_20_AUTO_SMUX_18CH );

    color16_write_register (COLOR16_REG_ENABLE, COLOR16_ENABLE_WEN |COLOR16_ENABLE_PON);// |COLOR16_ENABLE_SP_EN |COLOR16_ENABLE_PON );

}

void color16_read_data (color16_data_t *data_out)
{

	uint8_t status2;
	   	color16_read_register(COLOR16_REG_STATUS_2, &status2 );

	        if ( status2 & COLOR16_STATUS_2_AVALID )
	        {

	        	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	            uint8_t data_buf[ 38 ];
	            color16_generic_read (COLOR16_REG_STATUS, data_buf, 38 );


	                data_out->status = data_buf[ 0 ];
	                data_out->astatus = data_buf[ 1 ];
	                data_out->ch_fz = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
	                data_out->ch_fy = ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
	                data_out->ch_fxl = ( ( uint16_t ) data_buf[ 7 ] << 8 ) | data_buf[ 6 ];
	                data_out->ch_nir = ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 8 ];
	                data_out->ch_2x_vis_1 = ( ( uint16_t ) data_buf[ 11 ] << 8 ) | data_buf[ 10 ];
	                data_out->ch_fd_1 = ( ( uint16_t ) data_buf[ 13 ] << 8 ) | data_buf[ 12 ];
	                data_out->ch_f2 = ( ( uint16_t ) data_buf[ 15 ] << 8 ) | data_buf[ 14 ];
	                data_out->ch_f3 = ( ( uint16_t ) data_buf[ 17 ] << 8 ) | data_buf[ 16 ];
	                data_out->ch_f4 = ( ( uint16_t ) data_buf[ 19 ] << 8 ) | data_buf[ 18 ];
	                data_out->ch_f6 = ( ( uint16_t ) data_buf[ 21 ] << 8 ) | data_buf[ 20 ];
	                data_out->ch_2x_vis_2 = ( ( uint16_t ) data_buf[ 23 ] << 8 ) | data_buf[ 22 ];
	                data_out->ch_fd_2 = ( ( uint16_t ) data_buf[ 25 ] << 8 ) | data_buf[ 24 ];
	                data_out->ch_f1 = ( ( uint16_t ) data_buf[ 27 ] << 8 ) | data_buf[ 26 ];
	                data_out->ch_f5 = ( ( uint16_t ) data_buf[ 29 ] << 8 ) | data_buf[ 28 ];
	                data_out->ch_f7 = ( ( uint16_t ) data_buf[ 31 ] << 8 ) | data_buf[ 30 ];
	                data_out->ch_f8 = ( ( uint16_t ) data_buf[ 33 ] << 8 ) | data_buf[ 32 ];
	                data_out->ch_2x_vis_3 = ( ( uint16_t ) data_buf[ 35 ] << 8 ) | data_buf[ 34 ];
	                data_out->ch_fd_3 = ( ( uint16_t ) data_buf[ 37 ] << 8 ) | data_buf[ 36 ];
        }

}

