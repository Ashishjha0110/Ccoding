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
  char* filename;
  FILE *fp;
  struct stat filestatus;
  int file_size;
  char* file_contents;
  json_char* json;
  json_value* value;
       
  filename = "valid.json";

  FILE * Ldsetup; 
  char *plcdata;

  Ldsetup = fopen ("autoCodeSetup.c","w"); 
  plcdata = (char*)malloc(strlen("void ladder(void){"));
  strcpy(plcdata, "void ladder(void){");
  fputs(plcdata, Ldsetup);
  fputs("\n", Ldsetup);
  free(plcdata);
  fclose (Ldsetup);

  if ( stat(filename, &filestatus) != 0) {
    fprintf(stderr, "File %s not found\n", filename);
    return 1;
  }
  file_size = filestatus.st_size;
  printf("%d",file_size);

  file_contents = (char*)malloc(filestatus.st_size);
  if ( file_contents == NULL) {
    fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
    return 1;
  }
  fp = fopen(filename, "rt");
  if (fp == NULL) 
  {
    fprintf(stderr, "Unable to open %s\n", filename);
    fclose(fp);
    free(file_contents);
    return 1;
  }
  if ( fread(file_contents, file_size, 1, fp) != 1 )
  {
    fprintf(stderr, "Unable t read content of %s\n", filename);
    fclose(fp);
    free(file_contents);
    return 1;
  }
  fclose(fp);

  json = (json_char*)file_contents;

  value = json_parse(json,file_size);

  if (value == NULL) 
  {
    fprintf(stderr, "Unable to parse data\n");
    free(file_contents);
    exit(1);
  }
  process_value(value, 0);

  json_value_free(value);
  free(file_contents);

  Ldsetup = fopen ("autoCodeSetup.c","w"); 
  plcdata = (char*)malloc(strlen(" STPLC_setoneDO(channel_ name)"));
  strcpy(plcdata, " STPLC_setoneDO(channel_ name)");
  fputs(plcdata, Ldsetup);
  fputs("\n", Ldsetup);

  free(plcdata);
  plcdata = (char*)malloc(strlen("}"));
  strcpy(plcdata, "}");
  fputs(plcdata, Ldsetup);
  fputs("\n", Ldsetup);

  free(plcdata);
  fclose (Ldsetup);

  return 0;
}