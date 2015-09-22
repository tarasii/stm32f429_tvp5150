/**
  ******************************************************************************
  * File Name          : I2C.c
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

#include "gpio.h"
#include "dma.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_ENABLED;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_ENABLED;
  HAL_I2C_Init(&hi2c1);

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __I2C1_CLK_ENABLE();

    /* Peripheral DMA init*/
  
    hdma_i2c1_rx.Instance = DMA1_Stream0;
    hdma_i2c1_rx.Init.Channel = DMA_CHANNEL_1;
    hdma_i2c1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_i2c1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c1_rx.Init.MemInc = DMA_MINC_DISABLE;
    hdma_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c1_rx.Init.Mode = DMA_NORMAL;
    hdma_i2c1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_i2c1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_i2c1_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_i2c1_rx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_i2c1_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&hdma_i2c1_rx);

    __HAL_LINKDMA(hi2c,hdmarx,hdma_i2c1_rx);

    hdma_i2c1_tx.Instance = DMA1_Stream6;
    hdma_i2c1_tx.Init.Channel = DMA_CHANNEL_1;
    hdma_i2c1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_i2c1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_i2c1_tx.Init.MemInc = DMA_MINC_DISABLE;
    hdma_i2c1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.Mode = DMA_NORMAL;
    hdma_i2c1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_i2c1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_i2c1_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_i2c1_tx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_i2c1_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&hdma_i2c1_tx);

    __HAL_LINKDMA(hi2c,hdmatx,hdma_i2c1_tx);

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{

  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __I2C1_CLK_DISABLE();
  
    /**I2C1 GPIO Configuration    
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(hi2c->hdmarx);
    HAL_DMA_DeInit(hi2c->hdmatx);

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);

    HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);

  }
  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
} 

/* USER CODE BEGIN 1 */
void I2C1_WriteBuffer(uint8_t I2C_ADDRESS, uint8_t *aTxBuffer, uint8_t TXBUFFERSIZE) 
{
    /* -> Start the transmission process */
    /* While the I2C in reception process, user can transmit data through "aTxBuffer" buffer */
    while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)I2C_ADDRESS<<1, (uint8_t*)aTxBuffer, (uint16_t)TXBUFFERSIZE, (uint32_t)1000)!= HAL_OK)
    {
        /*
         * Error_Handler() function is called when Timeout error occurs.
         * When Acknowledge failure occurs (Slave don't acknowledge it's address)
         * Master restarts communication
         */
 
        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
        {
            //Error_Handler(3);
					  break;
        }
 
    }
 
    /* -> Wait for the end of the transfer */
    /* Before starting a new communication transfer, you need to check the current
     * state of the peripheral; if it’s busy you need to wait for the end of current
     * transfer before starting a new one.
     * For simplicity reasons, this example is just waiting till the end of the
     * transfer, but application may perform other tasks while transfer operation
     * is ongoing.
     */
      while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
      {
      }
}

void I2C1_ReadBuffer(uint8_t I2C_ADDRESS, uint8_t RegAddr, uint8_t *aRxBuffer, uint8_t RXBUFFERSIZE)
{
    /* -> Lets ask for register's address */
    I2C1_WriteBuffer(I2C_ADDRESS, &RegAddr, 1);
 
    /* -> Put I2C peripheral in reception process */
    while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)I2C_ADDRESS<<1, aRxBuffer, (uint16_t)RXBUFFERSIZE, (uint32_t)1000) != HAL_OK)
    {
        /* Error_Handler() function is called when Timeout error occurs.
         * When Acknowledge failure occurs (Slave don't acknowledge it's address)
         * Master restarts communication
         */
        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
        {
            //Error_Handler(4);
					  break;
        }
    }
 
    /* -> Wait for the end of the transfer */
    /* Before starting a new communication transfer, you need to check the current
     * state of the peripheral; if it’s busy you need to wait for the end of current
     * transfer before starting a new one.
     * For simplicity reasons, this example is just waiting till the end of the
     * transfer, but application may perform other tasks while transfer operation
     * is ongoing.
     **/
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY)
    {
    }
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
