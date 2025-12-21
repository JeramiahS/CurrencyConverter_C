#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

int main (int argc, char *argv[])
{
	//Validate user input
	if (argc < 2) {
		puts("Enter the arguments in the following format: 'amount codeConvertFrom codeConvertTo'");
		puts("Example: './CurrencyConverter 20 USD EUR'");
		exit(EXIT_SUCCESS);
	}
	char *end_ptr;
	const double VALUE = strtof(argv[1], &end_ptr);
	if (end_ptr == argv[1] || VALUE == 0.00F) {
		puts("First argument must be a numerical non-zero value.");
		printf("Your input: %s\n", end_ptr);
		exit(EXIT_FAILURE);
	}
	if (strlen(argv[2]) < 3 || strlen(argv[3]) < 3) {
		puts("Currency codes must be exactly three characters long.");
		exit(EXIT_FAILURE);
	}

	//Initialize cURL
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *handle_ptr = curl_easy_init();
	if (handle_ptr == NULL) {
		puts("cURL handle initialization failed.");
		curl_easy_cleanup(handle_ptr);
		curl_global_cleanup();
		exit(EXIT_FAILURE);
	}

	//Format request URL
	char url[128];
	sprintf(url, "https://api.fxratesapi.com/convert?from=%s&to=%s&amount=%.3f&format=tsv", argv[2], argv[3], VALUE);

	//Prepare error buffer in case of an error in sending the network request
	char error_buffer[CURL_ERROR_SIZE];

	//Set cURL options
	curl_easy_setopt(handle_ptr, CURLOPT_URL, url);
	curl_easy_setopt(handle_ptr, CURLOPT_ERRORBUFFER, error_buffer);

	//Send the GET request and print error if necessary
	CURLcode response = curl_easy_perform(handle_ptr);
	if (response != CURLE_OK) {
		size_t length = strlen(error_buffer);
		printf("\nlibcurl: (%d) ", response);
		if (length) {
			printf("%s%s", error_buffer, ((error_buffer[length - 1] != '\n') ? "\n" : ""));
		} else {
			printf("%s\n", curl_easy_strerror(response));
		}
	}

	//Perform cleanup operations before exiting the program
	curl_easy_cleanup(handle_ptr);
	curl_global_cleanup();

	return 0;
}
