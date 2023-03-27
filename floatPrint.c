

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "table.h"

#define ARROUT_LEN ( 40 )
#define NUM_EXPS 67

union {
  float f;
  uint32_t u;
} fu;
  //} fu = { .f = f };


void printRow( uint8_t row[] )
{
  int8_t idx;
  for( idx = ARROUT_LEN - 1; idx >= 0; idx-- )
  {
    if( idx == ( ARROUT_LEN / 2 ) ){ printf("."); }
    printf("%d",row[idx]);
  }
}

void addRow( uint8_t exp, uint8_t arrOut[] )
{
  uint8_t carry;
  uint8_t tmp;
  
  printf("exp is: %d\n",exp);
  // find location of decimal point, e.g.
  // "16.0000" -> 2
  // ".125" -> 0
  //int8_t row_num = exp-( (NUM_EXPS-1)/2);
  int8_t row_num = exp;
  const char **str = &table[ row_num ];
  int8_t idxLoc = 0;
  int8_t len = strnlen( *str, ARROUT_LEN );
  while( (*str[ idxLoc ] != '.' ) &&
	 ( idxLoc < len ) &&
	 ( idxLoc < ARROUT_LEN ) )
  {
    printf("[%c]",*str[idxLoc]);
    idxLoc++;
  }
  
  printf("\n");

  printf("before add  :");
  printRow(arrOut);
  printf("\n");
  
  // perform addition, Least sig dig first for carries
  printf("will add row: %s\n", *str );
  int8_t idx;
  int8_t str_idx = len - 1; // string counts backwards
  for( idx = 0 ; idx < len; idx++ )
  {
    tmp = arrOut[ idx ];
    printf( "%c", tmp + '0' );
    tmp += *str[ idx ] -'0';
    arrOut[ idxLoc + idx ] = tmp;
  }
  printf("\n");
  
  printf("after row : ");
  printRow(arrOut);
  printf("\n");
}

void floatPrint( float val )
{

  fu.f = val;
  printf("--------------\n");
  printf("will now print: %f\n", val );
  
  uint8_t sign =   ( fu.u & 0x80000000 ) >> 31;
  uint8_t exp  = ( ( fu.u & 0x7f000000 ) >> 24 ) - 31;
  uint8_t mant =   ( fu.u & 0x00ffffff );
  printf("exp field = %d\n", exp );

  uint8_t arrOut[ ARROUT_LEN ]={0};

  uint8_t expBit;
  for( expBit = 0; expBit < 6; expBit++ )
  {
    if( exp & ( 1 << expBit ) )
    {
      printf("---\n");
      addRow( exp, arrOut );
    }
  }

}
