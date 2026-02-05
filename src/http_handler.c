#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http_handler.h"

void print_conversion_result(char *argv[])
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *handle_ptr = curl_easy_init();

	if (handle_ptr == NULL) {
		fprintf(stderr, "cURL initialization failed.\n");
		curl_easy_cleanup(handle_ptr);
		curl_global_cleanup();
		exit(EXIT_FAILURE);
	}
	
	char url[128] = {0};
	snprintf(
		url,
		sizeof(url),
		"https://api.fxratesapi.com/convert?from=%s&to=%s&amount=%s&format=tsv",
		argv[2],
		argv[3],
		argv[1]
	);

	char error_buffer[CURL_ERROR_SIZE];

	curl_easy_setopt(handle_ptr, CURLOPT_URL, url);
	curl_easy_setopt(handle_ptr, CURLOPT_ERRORBUFFER, error_buffer);

	CURLcode response = curl_easy_perform(handle_ptr);
	
	if (response != CURLE_OK) {
		fprintf(stderr, "\nlibcurl (%d) ", response);
		exit(EXIT_FAILURE);
	}

	curl_easy_cleanup(handle_ptr);
	curl_global_cleanup();
}
