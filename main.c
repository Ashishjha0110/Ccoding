#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "json.h"

char* nodevalue;

//Function which reads all the node values
static void process_value(json_value* value, int depth); 

static void process_object(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.object.length;
        if(length>=1 && depth== 2 )
        {
          printf("%s \n",value->u.object.values[0].name);
        }
        for (x = 0; x < length; x++) {
          process_value(value->u.object.values[x].value, depth+1);
          if(depth== 4)
          {
            printf("= %s\n", value->u.object.values[x].name);
            printf("%s\n",nodevalue);
          }
        }
}

static void process_array(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.array.length;
       // printf("array\n");
        for (x = 0; x < length; x++) {
                process_value(value->u.array.values[x], depth);
        }
}

static void process_value(json_value* value, int depth)
{
        int j;
        if (value == NULL) {
                return;
        }
              switch (value->type) {
                case json_none:
                        printf("none\n");
                        break;
                case json_null:
                        printf("NULL\n");
                        break;        
                case json_object:
                        process_object(value, depth+1);
                        break;
                case json_array:
                        process_array(value, depth+1);
                        break;
                case json_integer:
                        printf("int: %10" PRId64 "\n", value->u.integer);
                        break;
                case json_double:
                        printf("double: %f\n", value->u.dbl);
                        break;
                case json_string:
                        free(nodevalue);
                        nodevalue = (char*)malloc(strlen(value->u.string.ptr));
                        strcpy(nodevalue, value->u.string.ptr);
                        //printf("string: %s\n", value->u.string.ptr);
                        break;
                case json_boolean:
                        printf("bool: %d\n", value->u.boolean);
                        break;
        }
}

int main ()
{
 
  FILE * Ldsetup; 
  char *plcdata;

  Ldsetup = fopen ("autoCodeSetup.c","w"); 
  free(plcdata);
  plcdata = (char*)malloc(strlen("void ladder(void){"));
  strcpy(plcdata, "void ladder(void){");
  fputs(plcdata, Ldsetup);
  fputs("\n", Ldsetup);

  /*free(plcdata);
  plcdata = (char*)malloc(strlen(" STPLC_setoneDO(channel_ name)"));
  strcpy(plcdata, " STPLC_setoneDO(channel_ name)");
  fputs(plcdata, Ldsetup);
  fputs("\n", Ldsetup);*/

  free(plcdata);
  plcdata = (char*)malloc(strlen("}"));
  strcpy(plcdata, "}");
  fputs(plcdata, Ldsetup);
  fputs("\n", Ldsetup);

  free(plcdata);
  fclose (Ldsetup);
  return 0;
}