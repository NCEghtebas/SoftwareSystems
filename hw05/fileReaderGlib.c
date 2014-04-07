#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <glib/gprintf.h>

int main(){
	GIOChannel *in_channel,*out_channel;
	gchar * result;
	gsize reslen;
	gsize resfin;	
	GError *error = NULL;
	GIOStatus stat;
	GString buf;
	gchar ** foo;
	GHashTable * wordcount= g_hash_table_new(g_str_hash, g_str_equal);
	int length;
	gpointer out;
	gpointer tempval;
	GList * keys;
	GList * values;
	
	in_channel = g_io_channel_new_file("TheKamaSutra.txt","r",&error);
	//in_channel = g_io_channel_new_file("untitled.txt","r",&error);

	for(int i=0; i <7811; i++){
		if(stat!= G_IO_STATUS_EOF){
			stat= g_io_channel_read_line(in_channel,&result,&reslen,&resfin,&error);
			//g_print("%s\n", result);
			foo = g_strsplit(result, " ", -1);

			for (int j=0; foo[j]!= NULL; j++){
				tempval= g_hash_table_lookup(wordcount, foo[j]);
				if(tempval != NULL){
					g_hash_table_insert(wordcount, (gpointer) foo[j], (gpointer)((int)tempval+1));
					//printf("%d\n", (int)tempval);
				}else{
					g_hash_table_insert(wordcount, (gpointer) foo[j], (gpointer)1);
					//printf("%d\n", (int)tempval);
				}
			}
	}
}
	values= g_hash_table_get_values(wordcount);
	keys= g_hash_table_get_keys(wordcount);
	for(int t=0; t<g_list_length(keys); t++){
		printf("key: %s \t value: %d\n",  (char *) g_list_nth_data(keys,t), (int) g_list_nth_data(values, t));
	}


	return 0;
}
