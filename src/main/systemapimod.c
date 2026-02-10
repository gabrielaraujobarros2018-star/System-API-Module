/* 
systemapimod.c (System API Module).
Inspiration by Sololearn!
*/

#include <stdio.h>
#include <stdlib.h> // Header to Access of memory management
#include <string.h>
#include <time.h>
#include <unistd.h>  // For potential mobile-specific delays or checks
#include <curl/curl.h>  // libcurl for HTTP API calls
#include <cjson/cJSON.h> // cJSON for JSON parsing (needs to be installed)
#include <errno.h>
#include <setjmp.h>  // For recovery points

// Module struct
struct os {
    int apimodel;
    int system;
    char osname[1];
};

int main() {
    // 2 vars
    struct os h1;
    struct api h1;
    
    h1.os = 1;
    h1.apimodel = 1;
    sprintf(h1.os, "Lumen");
    
    h2.osname = 1;
    h2.hostnum = 5432;
    sprintf(h2.osname, "Lumen");
    
    printf("MainOSName: %s, %d\n", h2.osname, h2.hostnum);
    printf("MainAPIModel: %s, %d\n", h2.apimodel, h2.os);
    
    return 0;
}

// ---------------------------------------------------
/* Memory Management:
With Calloc, Malloc, and Free.
Also, logging.
*/

// ---- Malloc! ----
// Define platform-specific macros for Lumen OS on Moto Nexus 6 (Armv7-A)
#if defined(__arm__) && defined(__ARM_ARCH_7A__)
#define LUMEN_OS_TARGET 1
#define DEVICE_MODEL "Moto Nexus 6"
#else
#error "This code is tailored for Lumen OS on Armv7-A architecture (Moto Nexus 6)"
#endif

// Custom struct for memory management in Lumen environment
typedef struct {
    size_t block_size;
    int *data_ptr;
    char device_info[64];
} LumenMemBlock;

// Function to initialize and allocate memory with Lumen-specific checks
LumenMemBlock* lumen_alloc_init(size_t num_elements) {
    LumenMemBlock* mem = (LumenMemBlock*)calloc(1, sizeof(LumenMemBlock));
    if (mem == NULL) {
        return NULL;
    }
    
    mem->block_size = num_elements;
    mem->data_ptr = (int*)calloc(num_elements, sizeof(int));
    if (mem->data_ptr == NULL) {
        free(mem);
        return NULL;
    }
    
    // Embed device info for Lumen OS verification
    strncpy(mem->device_info, DEVICE_MODEL, sizeof(mem->device_info) - 1);
    mem->device_info[sizeof(mem->device_info) - 1] = '\0';
    
    return mem;
}

// Function to set value in the allocated block with offset
void lumen_set_value(LumenMemBlock* mem, size_t offset, int value) {
    if (mem != NULL && mem->data_ptr != NULL && offset < mem->block_size) {
        mem->data_ptr[offset] = value;
    }
}

// Function to retrieve and print value with Lumen-style logging
void lumen_print_value(LumenMemBlock* mem, size_t offset) {
    if (mem != NULL && mem->data_ptr != NULL && offset < mem->block_size) {
#ifdef LUMEN_OS_TARGET
        // Simulate Lumen OS logging (e.g., for mobile console)
        printf("Lumen OS on %s: Element at offset %zu is %d\n", 
               mem->device_info, offset, mem->data_ptr[offset]);
#else
        printf("Element at offset %zu: %d\n", offset, mem->data_ptr[offset]);
#endif
    } else {
        printf("Error: Invalid memory block or offset\n");
    }
}

// Function to cleanup memory
void lumen_free_block(LumenMemBlock* mem) {
    if (mem != NULL) {
        free(mem->data_ptr);
        free(mem);
    }
}

int main() {
    // Allocate for 15 elements (modified from original 10)
    LumenMemBlock* block = lumen_alloc_init(15);
    if (block == NULL) {
        printf("Allocation failed on Lumen OS\n");
        return 1;
    }
    
    // Set value at fourth position (modified from third)
    lumen_set_value(block, 3, 75);  // Modified value from 50
    
    // Add a loop to set more values for heavier modification
    for (size_t i = 0; i < block->block_size; ++i) {
        if (i != 3) {
            lumen_set_value(block, i, (int)i * 2);
        }
    }
    
    // Print the specific value
    lumen_print_value(block, 3);
    
    // Print another value to demonstrate
    lumen_print_value(block, 0);
    lumen_print_value(block, 14);
    
    // Simulate some Lumen OS delay (e.g., for mobile responsiveness)
    usleep(100000);  // 0.1 second delay
    
    // Cleanup
    lumen_free_block(block);
    
    return 0;
}

// ---- Calloc ----
// Platform-specific definitions for Lumen on Armv7-A Moto Nexus 6
#if defined(__arm__) && defined(__ARM_ARCH_7A__)
#define LUMEN_PLATFORM 1
#define TARGET_DEVICE "Moto Nexus 6"
#else
#error "Code optimized for Lumen OS on Armv7-A (Moto Nexus 6 only)"
#endif

// Enhanced struct for calloc-based allocation in Lumen context
typedef struct {
    size_t alloc_count;
    double *values;  // Changed to double for variety
    char platform_tag[128];
} LumenAllocUnit;

// Initialize allocation unit with calloc and embed platform details
LumenAllocUnit* init_lumen_alloc(size_t elements) {
    LumenAllocUnit* unit = (LumenAllocUnit*)calloc(1, sizeof(LumenAllocUnit));
    if (unit == NULL) {
        return NULL;
    }
    
    unit->alloc_count = elements;
    unit->values = (double*)calloc(elements, sizeof(double));
    if (unit->values == NULL) {
        free(unit);
        return NULL;
    }
    
    // Tag with device info for Lumen verification
    snprintf(unit->platform_tag, sizeof(unit->platform_tag), "Lumen OS - %s", TARGET_DEVICE);
    
    return unit;
}

// Function to assign a value at a given index
void assign_lumen_value(LumenAllocUnit* unit, size_t idx, double val) {
    if (unit != NULL && unit->values != NULL && idx < unit->alloc_count) {
        unit->values[idx] = val;
    }
}

// Function to display value with Lumen-specific output
void display_lumen_value(LumenAllocUnit* unit, size_t idx) {
    if (unit != NULL && unit->values != NULL && idx < unit->alloc_count) {
#ifdef LUMEN_PLATFORM
        // Lumen mobile-friendly print
        printf("%s: Value at index %zu is %.2f\n", unit->platform_tag, idx, unit->values[idx]);
#else
        printf("Value at %zu: %.2f\n", idx, unit->values[idx]);
#endif
    } else {
        printf("Allocation error or invalid index\n");
    }
}

// Release the allocation unit
void release_lumen_unit(LumenAllocUnit* unit) {
    if (unit != NULL) {
        free(unit->values);
        free(unit);
    }
}

int main() {
    // Allocate for 20 elements (increased from original concept)
    LumenAllocUnit* alloc = init_lumen_alloc(20);
    if (alloc == NULL) {
        printf("Failed to allocate on Lumen OS\n");
        return 1;
    }
    
    // Assign value at fifth position (shifted from third)
    assign_lumen_value(alloc, 4, 88.5);  // Different value and type
    
    // Populate additional values in a loop for modification depth
    for (size_t j = 0; j < alloc->alloc_count; ++j) {
        if (j != 4) {
            assign_lumen_value(alloc, j, (double)j * 1.5);
        }
    }
    
    // Display selected values
    display_lumen_value(alloc, 4);
    display_lumen_value(alloc, 1);
    display_lumen_value(alloc, 19);
    
    // Add delay to mimic Lumen OS mobile operation
    usleep(200000);  // 0.2s pause
    
    // Free resources
    release_lumen_unit(alloc);
    
    return 0;
}

// ---- Free ----
// Define macros specific to Lumen OS on Armv7-A Moto Nexus 6
#if defined(__arm__) && defined(__ARM_ARCH_7A__)
#define LUMEN_ENV 1
#define HARDWARE_MODEL "Moto Nexus 6"
#else
#error "Optimized for Lumen OS running on Armv7-A (Moto Nexus 6)"
#endif

// Struct for managing freed memory in Lumen context
typedef struct {
    size_t freed_size;
    void *mem_ptr;
    char hardware_label[96];
    int status_code;
} LumenFreeManager;

// Function to prepare a memory manager for allocation and later free
LumenFreeManager* setup_lumen_manager(size_t alloc_bytes) {
    LumenFreeManager* manager = (LumenFreeManager*)malloc(sizeof(LumenFreeManager));
    if (manager == NULL) {
        return NULL;
    }
    
    manager->mem_ptr = malloc(alloc_bytes);
    if (manager->mem_ptr == NULL) {
        free(manager);
        return NULL;
    }
    
    manager->freed_size = 0;  // Initially not freed
    manager->status_code = 0; // Success code
    
    // Embed hardware info for Lumen OS
    snprintf(manager->hardware_label, sizeof(manager->hardware_label), "Allocated on %s under Lumen", HARDWARE_MODEL);
    
    return manager;
}

// Function to perform free operation with checks
void execute_lumen_free(LumenFreeManager* manager) {
    if (manager != NULL && manager->mem_ptr != NULL && manager->freed_size == 0) {
        free(manager->mem_ptr);
        manager->mem_ptr = NULL;
        manager->freed_size = 1;  // Mark as freed
        manager->status_code = 1; // Freed successfully
    } else {
        manager->status_code = -1; // Error in freeing
    }
}

// Function to log the free status in Lumen style
void log_lumen_status(LumenFreeManager* manager) {
    if (manager != NULL) {
#ifdef LUMEN_ENV
        // Lumen-specific logging for mobile
        printf("%s: Free status - %s (code: %d)\n", 
               manager->hardware_label, 
               (manager->status_code == 1) ? "Success" : "Failed", 
               manager->status_code);
#else
        printf("Free operation: %s (code: %d)\n", 
               (manager->status_code == 1) ? "Success" : "Failed", 
               manager->status_code);
#endif
    } else {
        printf("Manager invalid\n");
    }
}

// Function to destroy the manager struct
void destroy_lumen_manager(LumenFreeManager* manager) {
    if (manager != NULL) {
        if (manager->mem_ptr != NULL) {
            free(manager->mem_ptr);  // Safety free if not already
        }
        free(manager);
    }
}

int main() {
    // Allocate 256 bytes (arbitrary size for example)
    LumenFreeManager* mgr = setup_lumen_manager(256);
    if (mgr == NULL) {
        printf("Setup failed on Lumen OS\n");
        return 1;
    }
    
    // Simulate usage: memset to fill memory
    memset(mgr->mem_ptr, 0xAA, 256);
    
    // Now free it
    execute_lumen_free(mgr);
    
    // Log the result
    log_lumen_status(mgr);
    
    // Additional checks: try to free again (should fail)
    execute_lumen_free(mgr);
    log_lumen_status(mgr);
    
    // Delay for Lumen mobile simulation
    usleep(150000);  // 0.15s
    
    // Cleanup manager
    destroy_lumen_manager(mgr);
    
    return 0;
}

// ---- Logging ----
// Platform guards for Lumen OS on Armv7-A Moto Nexus 6
#if defined(__arm__) && defined(__ARM_ARCH_7A__)
#define LUMEN_SYSTEM 1
#define DEVICE_SPEC "Moto Nexus 6"
#else
#error "Designed exclusively for Lumen OS on Armv7-A (Moto Nexus 6)"
#endif

// Struct for logging operations in Lumen environment
typedef struct {
    char log_buffer[512];
    char device_marker[128];
    int log_level;
    time_t timestamp;
    int status_flag;
} LumenLogHandler;

// Initialize the log handler with device specifics
LumenLogHandler* create_lumen_logger(int level) {
    LumenLogHandler* handler = (LumenLogHandler*)malloc(sizeof(LumenLogHandler));
    if (handler == NULL) {
        return NULL;
    }
    
    handler->log_level = level;
    handler->status_flag = 0;  // Initialized
    time(&handler->timestamp);
    
    // Set device marker for logs
    snprintf(handler->device_marker, sizeof(handler->device_marker), "[Lumen OS - %s]", DEVICE_SPEC);
    
    return handler;
}

// Function to record a log message with timestamp and level
void record_lumen_log(LumenLogHandler* handler, const char* message, int level) {
    if (handler == NULL || message == NULL) {
        return;
    }
    
    if (level >= handler->log_level) {
        struct tm* time_info = localtime(&handler->timestamp);
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
        
        snprintf(handler->log_buffer, sizeof(handler->log_buffer), 
                 "%s %s [Level %d]: %s\n", 
                 handler->device_marker, time_str, level, message);
        
        handler->status_flag = 1;  // Logged
    } else {
        handler->status_flag = -1;  // Level too low
    }
}

// Function to output the log with Lumen-specific handling
void output_lumen_log(LumenLogHandler* handler) {
    if (handler != NULL && handler->status_flag == 1) {
#ifdef LUMEN_SYSTEM
        // Simulate Lumen mobile logging (e.g., to console or file)
        printf("%s", handler->log_buffer);
#else
        printf("Log: %s", handler->log_buffer);
#endif
        // Reset buffer after output
        memset(handler->log_buffer, 0, sizeof(handler->log_buffer));
    } else {
        printf("No log to output or error occurred\n");
    }
}

// Function to release the logger resources
void release_lumen_logger(LumenLogHandler* handler) {
    if (handler != NULL) {
        free(handler);
    }
}

int main() {
    // Create logger with minimum level 2
    LumenLogHandler* logger = create_lumen_logger(2);
    if (logger == NULL) {
        printf("Logger creation failed on Lumen OS\n");
        return 1;
    }
    
    // Record some logs
    record_lumen_log(logger, "System boot initiated", 3);
    output_lumen_log(logger);
    
    record_lumen_log(logger, "Debug info: Memory check passed", 1);  // Below level, skipped
    output_lumen_log(logger);
    
    record_lumen_log(logger, "Warning: Low battery detected", 2);
    output_lumen_log(logger);
    
    // Update timestamp for next logs
    time(&logger->timestamp);
    
    record_lumen_log(logger, "Error: Connection timeout", 4);
    output_lumen_log(logger);
    
    // Delay to simulate Lumen OS processing
    usleep(250000);  // 0.25s
    
    // Release
    release_lumen_logger(logger);
    
    return 0;
}

// Function to initialize on boot

// Texts

// ---- API data collection ----

// Fixed API Module struct - using flexible array member for osname
struct os {
    int apimodel;
    int system;
    char osname[1];  // Flexible array member - allocate more space at runtime
};

// Callback for curl to collect response data
struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        printf("Not enough memory (realloc returned NULL)
");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

// Function to collect API data and populate struct
int collect_api_data(struct os *api_data, const char *api_url) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;
    
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api_url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s
", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            free(chunk.memory);
            return -1;
        }
        
        curl_easy_cleanup(curl);
    }
    
    // Parse JSON response (example assumes API returns system info)
    cJSON *json = cJSON_Parse(chunk.memory);
    if (json != NULL) {
        // Example: extract apimodel and system from JSON response
        cJSON *apimodel_json = cJSON_GetObjectItem(json, "apimodel");
        cJSON *system_json = cJSON_GetObjectItem(json, "system");
        cJSON *osname_json = cJSON_GetObjectItem(json, "osname");
        
        if (apimodel_json) api_data->apimodel = apimodel_json->valueint;
        if (system_json) api_data->system = system_json->valueint;
        if (osname_json && cJSON_IsString(osname_json)) {
            strncpy(api_data->osname, osname_json->valuestring, 99);
            api_data->osname[99] = '';
        }
        
        cJSON_Delete(json);
    }
    
    free(chunk.memory);
    return 0;
}

int main() {
    // Allocate space for struct + osname string (100 chars)
    struct os *h1 = malloc(sizeof(struct os) + 100);
    if (!h1) {
        printf("Memory allocation failed
");
        return 1;
    }
    
    // Collect data from internal API
    const char *internal_api = "http://localhost:8080/api/system-info";
    if (collect_api_data(h1, internal_api) == 0) {
        printf("API Data Collected:
");
        printf("OS Name: %s
", h1->osname);
        printf("API Model: %d
", h1->apimodel);
        printf("System ID: %d
", h1->system);
    } else {
        // Fallback values if API fails
        h1->apimodel = 1;
        h1->system = 1;
        strcpy(h1->osname, "Lumen");
        printf("Using fallback values
");
    }
    
    free(h1);
    return 0;
}

// Redirect to Website

// ---- Error handling ----

// API Module struct with proper size
struct os {
    int apimodel;
    int system;
    char osname[100];  // Fixed size for simplicity
};

// Error codes
enum API_ERROR {
    API_SUCCESS = 0,
    API_MEM_ERROR = -1,
    API_CURL_INIT_ERROR = -2,
    API_NETWORK_ERROR = -3,
    API_JSON_PARSE_ERROR = -4,
    API_STRUCT_INIT_ERROR = -5
};

// Callback for curl with error handling
struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "realloc failed: %s
", strerror(errno));
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

// Safe initialization of struct
int init_api_struct(struct os *api_data) {
    if (!api_data) {
        fprintf(stderr, "Error: NULL pointer passed to init_api_struct
");
        return API_STRUCT_INIT_ERROR;
    }
    
    api_data->apimodel = 0;
    api_data->system = 0;
    api_data->osname[0] = '';
    return API_SUCCESS;
}

// Collect API data with full error handling
int collect_api_data(struct os *api_data, const char *api_url) {
    CURL *curl = NULL;
    CURLcode res;
    struct MemoryStruct chunk = {0};
    int result = API_SUCCESS;
    
    // Validate inputs
    if (!api_data || !api_url) {
        fprintf(stderr, "Error: NULL api_data or api_url
");
        return API_STRUCT_INIT_ERROR;
    }
    
    // Initialize memory chunk
    chunk.memory = malloc(1);
    if (!chunk.memory) {
        fprintf(stderr, "Error: Failed to allocate memory for response buffer
");
        return API_MEM_ERROR;
    }
    chunk.size = 0;
    
    // Initialize curl
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error: curl_easy_init failed
");
        free(chunk.memory);
        return API_CURL_INIT_ERROR;
    }
    
    // Configure curl
    curl_easy_setopt(curl, CURLOPT_URL, api_url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    // Perform request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: curl_easy_perform failed: %s
", curl_easy_strerror(res));
        result = API_NETWORK_ERROR;
        goto cleanup;
    }
    
    // Check if we got any data
    if (chunk.size == 0) {
        fprintf(stderr, "Warning: Empty response from API
");
    }
    
    // Parse JSON response
    cJSON *json = cJSON_Parse(chunk.memory);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr) {
            fprintf(stderr, "Error: JSON parse failed at: %s
", error_ptr);
        } else {
            fprintf(stderr, "Error: JSON parse failed (unknown reason)
");
        }
        result = API_JSON_PARSE_ERROR;
        goto cleanup;
    }
    
    // Extract data safely
    cJSON *apimodel_json = cJSON_GetObjectItem(json, "apimodel");
    cJSON *system_json = cJSON_GetObjectItem(json, "system");
    cJSON *osname_json = cJSON_GetObjectItem(json, "osname");
    
    if (cJSON_IsNumber(apimodel_json)) {
        api_data->apimodel = apimodel_json->valueint;
    } else {
        fprintf(stderr, "Warning: Invalid or missing apimodel field
");
        api_data->apimodel = -1;  // Error value
    }
    
    if (cJSON_IsNumber(system_json)) {
        api_data->system = system_json->valueint;
    } else {
        fprintf(stderr, "Warning: Invalid or missing system field
");
        api_data->system = -1;
    }
    
    if (cJSON_IsString(osname_json) && osname_json->valuestring) {
        strncpy(api_data->osname, osname_json->valuestring, sizeof(api_data->osname) - 1);
        api_data->osname[sizeof(api_data->osname) - 1] = '';
    } else {
        fprintf(stderr, "Warning: Invalid or missing osname field
");
        strcpy(api_data->osname, "Unknown");
    }
    
cleanup:
    if (json) cJSON_Delete(json);
    curl_easy_cleanup(curl);
    free(chunk.memory);
    return result;
}

// Print results with status
void print_api_data(const struct os *api_data, int status) {
    printf("=== API Data Collection Results ===
");
    printf("Status: ");
    
    switch (status) {
        case API_SUCCESS:
            printf("SUCCESS
");
            break;
        case API_MEM_ERROR:
            printf("MEMORY ALLOCATION FAILED
");
            break;
        case API_CURL_INIT_ERROR:
            printf("CURL INITIALIZATION FAILED
");
            break;
        case API_NETWORK_ERROR:
            printf("NETWORK/CURL REQUEST FAILED
");
            break;
        case API_JSON_PARSE_ERROR:
            printf("JSON PARSING FAILED
");
            break;
        case API_STRUCT_INIT_ERROR:
            printf("STRUCT INITIALIZATION FAILED
");
            break;
        default:
            printf("UNKNOWN ERROR (%d)
", status);
    }
    
    printf("API Model: %d
", api_data->apimodel);
    printf("System ID: %d
", api_data->system);
    printf("OS Name: %s
", api_data->osname);
    printf("==============================
");
}

int main() {
    struct os api_data;
    int status;
    const char *internal_api = "http://localhost:8080/api/system-info";
    
    // Initialize curl globally
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Initialize struct
    status = init_api_struct(&api_data);
    if (status != API_SUCCESS) {
        fprintf(stderr, "Failed to initialize API struct
");
        curl_global_cleanup();
        return 1;
    }
    
    // Try to collect data
    printf("Attempting to collect data from: %s
", internal_api);
    status = collect_api_data(&api_data, internal_api);
    
    // Always print results (even on error)
    print_api_data(&api_data, status);
    
    // Apply fallback values only if critical fields are invalid
    if (status != API_SUCCESS || api_data.apimodel == -1 || api_data.system == -1) {
        printf("Applying fallback values...
");
        api_data.apimodel = 1;
        api_data.system = 1;
        strcpy(api_data.osname, "Lumen");
    }
    
    curl_global_cleanup();
    return (status == API_SUCCESS) ? 0 : 1;
}

// ---- Recovery ----

// API Module struct
struct os {
    int apimodel;
    int system;
    char osname[100];
};

// Enhanced error codes with recovery states
enum API_ERROR {
    API_SUCCESS = 0,
    API_MEM_ERROR = -1,
    API_CURL_INIT_ERROR = -2,
    API_NETWORK_ERROR = -3,
    API_JSON_PARSE_ERROR = -4,
    API_STRUCT_INIT_ERROR = -5,
    API_RECOVERY_SUCCESS = 10,  // Recovery completed
    API_MAX_RETRIES = -99       // Max retries exceeded
};

// Recovery context
struct recovery_ctx {
    jmp_buf env;
    int retry_count;
    int max_retries;
    struct os backup_data;
    int recovery_active;
};

// Callback for curl (unchanged)
struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "RECV: Memory reallocation failed
");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

// Initialize recovery context with backup data
int init_recovery_ctx(struct recovery_ctx *ctx, struct os *backup) {
    if (!ctx || !backup) return API_STRUCT_INIT_ERROR;
    
    ctx->retry_count = 0;
    ctx->max_retries = 3;
    ctx->recovery_active = 0;
    
    // Store backup data
    memcpy(&ctx->backup_data, backup, sizeof(struct os));
    
    if (setjmp(ctx->env) == 0) {
        return API_SUCCESS;
    }
    return API_RECOVERY_SUCCESS;  // Returning from longjmp
}

// Safe struct initialization with recovery backup
int init_api_struct(struct os *api_data, struct os *backup) {
    if (!api_data || !backup) {
        fprintf(stderr, "RECOV: NULL pointer in init_api_struct
");
        return API_STRUCT_INIT_ERROR;
    }
    
    // Initialize with backup values first
    memcpy(api_data, backup, sizeof(struct os));
    
    return API_SUCCESS;
}

// RETRY WITH BACKOFF: Core recovery mechanism
int collect_api_data_with_recovery(struct os *api_data, const char *api_url, struct recovery_ctx *ctx) {
    CURL *curl = NULL;
    CURLcode res;
    struct MemoryStruct chunk = {0};
    const char *backup_urls[] = {
        "http://localhost:8080/api/system-info",
        "http://127.0.0.1:8080/api/system-info",
        "http://localhost:3000/api/system",
        NULL
    };
    
    // Check if already in recovery mode
    if (ctx->recovery_active) {
        longjmp(ctx->env, API_RECOVERY_SUCCESS);
    }
    
    for (int url_idx = 0; backup_urls[url_idx]; url_idx++) {
        ctx->retry_count = 0;
        
        while (ctx->retry_count < ctx->max_retries) {
            // Initialize for this attempt
            chunk.memory = malloc(1);
            if (!chunk.memory) {
                fprintf(stderr, "RECOV: Alloc failed, using backup
");
                memcpy(api_data, &ctx->backup_data, sizeof(struct os));
                return API_RECOVERY_SUCCESS;
            }
            chunk.size = 0;
            
            curl = curl_easy_init();
            if (!curl) {
                ctx->retry_count++;
                free(chunk.memory);
                if (ctx->retry_count >= ctx->max_retries) {
                    fprintf(stderr, "RECOV: Curl init failed after %d retries
", ctx->retry_count);
                    goto use_backup;
                }
                sleep(1 << ctx->retry_count);  // Exponential backoff
                continue;
            }
            
            // Configure with increasing timeout
            curl_easy_setopt(curl, CURLOPT_URL, backup_urls[url_idx]);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L + (2L * ctx->retry_count));
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3L + ctx->retry_count);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            
            // Enter recovery mode for this request
            ctx->recovery_active = 1;
            res = curl_easy_perform(curl);
            ctx->recovery_active = 0;
            
            curl_easy_cleanup(curl);
            free(chunk.memory);
            
            if (res == CURLE_OK && chunk.size > 0) {
                // Try JSON parse (simplified for brevity)
                cJSON *json = cJSON_Parse(chunk.memory ? chunk.memory : "{}");
                if (json) {
                    // Extract data safely (same as before)
                    cJSON *apimodel_json = cJSON_GetObjectItem(json, "apimodel");
                    cJSON *system_json = cJSON_GetObjectItem(json, "system");
                    cJSON *osname_json = cJSON_GetObjectItem(json, "osname");
                    
                    if (cJSON_IsNumber(apimodel_json)) api_data->apimodel = apimodel_json->valueint;
                    if (cJSON_IsNumber(system_json)) api_data->system = system_json->valueint;
                    if (cJSON_IsString(osname_json)) strncpy(api_data->osname, osname_json->valuestring, 99);
                    
                    cJSON_Delete(json);
                    return API_SUCCESS;  // SUCCESS!
                }
            }
            
            ctx->retry_count++;
            fprintf(stderr, "RECOV: Attempt %d/%d failed for %s, backoff %ds
", 
                   ctx->retry_count, ctx->max_retries, backup_urls[url_idx], 1 << ctx->retry_count);
            
            if (ctx->retry_count >= ctx->max_retries) {
                fprintf(stderr, "RECOV: All retries failed for %s
", backup_urls[url_idx]);
            }
            
            sleep(1 << (ctx->retry_count - 1));  // Backoff before next URL
        }
    }
    
use_backup:
    // Final recovery: restore backup data
    fprintf(stderr, "RECOV: All endpoints failed, restoring backup data
");
    memcpy(api_data, &ctx->backup_data, sizeof(struct os));
    return API_RECOVERY_SUCCESS;
}

void print_recovery_status(struct os *data, int status, struct recovery_ctx *ctx) {
    printf("
=== RECOVERY REPORT ===
");
    printf("Final Status: ");
    
    switch (status) {
        case API_SUCCESS: printf("FULL SUCCESS
"); break;
        case API_RECOVERY_SUCCESS: printf("RECOVERY SUCCESS (using backup/fallback)
"); break;
        default: printf("HARD FAILURE (code: %d)
", status);
    }
    
    printf("Retries Used: %d/%d
", ctx->retry_count, ctx->max_retries);
    printf("API Model: %d | System: %d | OS: %s
", 
           data->apimodel, data->system, data->osname);
    printf("==================

");
}

int main() {
    struct os api_data, backup_data;
    struct recovery_ctx ctx;
    
    // Setup fallback data
    backup_data.apimodel = 1;
    backup_data.system = 1;
    strcpy(backup_data.osname, "Lumen");
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Initialize recovery system FIRST
    if (init_recovery_ctx(&ctx, &backup_data) != API_SUCCESS) {
        fprintf(stderr, "CRITICAL: Recovery init failed
");
        curl_global_cleanup();
        return 1;
    }
    
    // Initialize main data from backup
    init_api_struct(&api_data, &backup_data);
    
    printf("🚀 Starting API collection with recovery...
");
    int status = collect_api_data_with_recovery(&api_data, "http://localhost:8080/api/system-info", &ctx);
    
    print_recovery_status(&api_data, status, &ctx);
    
    curl_global_cleanup();
    return (status == API_SUCCESS) ? 0 : 1;
}

// Auth

// API Module struct
struct os {
    int apimodel;
    int system;
    char osname[100];
};

// Enhanced error codes
enum API_ERROR {
    API_SUCCESS = 0,
    API_MEM_ERROR = -1,
    API_CURL_INIT_ERROR = -2,
    API_NETWORK_ERROR = -3,
    API_JSON_PARSE_ERROR = -4,
    API_AUTH_ERROR = -6,      // NEW: Authentication failure
    API_STRUCT_INIT_ERROR = -5,
    API_RECOVERY_SUCCESS = 10,
    API_MAX_RETRIES = -99
};

// Auth credentials structure
struct auth_config {
    char username[64];
    char password[64];
    char bearer_token[256];
    int use_basic_auth;
    int use_bearer_auth;
};

// Recovery context (unchanged)
struct recovery_ctx {
    jmp_buf env;
    int retry_count;
    int max_retries;
    struct os backup_data;
    int recovery_active;
};

// Memory callback (unchanged)
struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "AUTH: Memory reallocation failed
");
        return 0;
    }
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

// NEW: Initialize authentication config
int init_auth_config(struct auth_config *auth, const char *username, const char *password) {
    if (!auth || !username) {
        fprintf(stderr, "AUTH: Invalid auth config parameters
");
        return API_STRUCT_INIT_ERROR;
    }
    
    memset(auth, 0, sizeof(struct auth_config));
    strncpy(auth->username, username, sizeof(auth->username) - 1);
    if (password) {
        strncpy(auth->password, password, sizeof(auth->password) - 1);
    }
    
    auth->use_basic_auth = 1;  // Default to Basic Auth
    return API_SUCCESS;
}

// NEW: Initialize Bearer token auth
int set_bearer_token(struct auth_config *auth, const char *token) {
    if (!auth || !token) return API_STRUCT_INIT_ERROR;
    
    strncpy(auth->bearer_token, token, sizeof(auth->bearer_token) - 1);
    auth->use_bearer_auth = 1;
    auth->use_basic_auth = 0;  // Disable basic auth
    return API_SUCCESS;
}

// Recovery init (unchanged)
int init_recovery_ctx(struct recovery_ctx *ctx, struct os *backup) {
    if (!ctx || !backup) return API_STRUCT_INIT_ERROR;
    
    ctx->retry_count = 0;
    ctx->max_retries = 3;
    ctx->recovery_active = 0;
    memcpy(&ctx->backup_data, backup, sizeof(struct os));
    
    if (setjmp(ctx->env) == 0) {
        return API_SUCCESS;
    }
    return API_RECOVERY_SUCCESS;
}

int init_api_struct(struct os *api_data, struct os *backup) {
    if (!api_data || !backup) return API_STRUCT_INIT_ERROR;
    memcpy(api_data, backup, sizeof(struct os));
    return API_SUCCESS;
}

// ENHANCED: API collection with FULL AUTH SUPPORT
int collect_api_data_with_recovery(struct os *api_data, const char *api_url, 
                                  struct recovery_ctx *ctx, struct auth_config *auth) {
    CURL *curl = NULL;
    CURLcode res;
    struct MemoryStruct chunk = {0};
    long http_status = 0;
    
    const char *backup_urls[] = {
        "http://localhost:8080/api/system-info",
        "http://127.0.0.1:8080/api/system-info",
        "http://localhost:3000/api/system",
        NULL
    };
    
    if (ctx->recovery_active) {
        longjmp(ctx->env, API_RECOVERY_SUCCESS);
    }
    
    for (int url_idx = 0; backup_urls[url_idx]; url_idx++) {
        ctx->retry_count = 0;
        
        while (ctx->retry_count < ctx->max_retries) {
            // Allocate memory
            chunk.memory = malloc(1);
            if (!chunk.memory) {
                memcpy(api_data, &ctx->backup_data, sizeof(struct os));
                return API_RECOVERY_SUCCESS;
            }
            chunk.size = 0;
            
            curl = curl_easy_init();
            if (!curl) {
                ctx->retry_count++;
                free(chunk.memory);
                if (ctx->retry_count >= ctx->max_retries) goto use_backup;
                sleep(1 << ctx->retry_count);
                continue;
            }
            
            // CORE CURL SETUP
            curl_easy_setopt(curl, CURLOPT_URL, backup_urls[url_idx]);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L + (2L * ctx->retry_count));
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
            
            // *** AUTHENTICATION SETUP ***
            if (auth->use_basic_auth) {
                char credentials[128];
                snprintf(credentials, sizeof(credentials), "%s:%s", 
                        auth->username, auth->password[0] ? auth->password : "");
                curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
                curl_easy_setopt(curl, CURLOPT_USERNAME, auth->username);
                curl_easy_setopt(curl, CURLOPT_PASSWORD, auth->password);
                printf("🔐 Using Basic Auth: %s:***
", auth->username);
            }
            
            if (auth->use_bearer_auth && strlen(auth->bearer_token) > 0) {
                struct curl_slist *headers = NULL;
                char auth_header[300];
                snprintf(auth_header, sizeof(auth_header), 
                        "Authorization: Bearer %s", auth->bearer_token);
                headers = curl_slist_append(headers, auth_header);
                headers = curl_slist_append(headers, "Accept: application/json");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                printf("🔐 Using Bearer Token
");
            }
            
            // Get HTTP status code
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
            
            // EXECUTE WITH RECOVERY
            ctx->recovery_active = 1;
            res = curl_easy_perform(curl);
            ctx->recovery_active = 0;
            
            // Check HTTP status
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
            
            curl_slist_free_all(curl_easy_getinfo(curl, CURLINFO_HTTPHEADER, NULL));
            curl_easy_cleanup(curl);
            free(chunk.memory);
            
            // AUTHENTICATION SUCCESS CHECK
            if (res == CURLE_OK && http_status == 200 && chunk.size > 0) {
                cJSON *json = cJSON_Parse(chunk.memory);
                if (json) {
                    cJSON *apimodel_json = cJSON_GetObjectItem(json, "apimodel");
                    cJSON *system_json = cJSON_GetObjectItem(json, "system");
                    cJSON *osname_json = cJSON_GetObjectItem(json, "osname");
                    
                    if (cJSON_IsNumber(apimodel_json)) api_data->apimodel = apimodel_json->valueint;
                    if (cJSON_IsNumber(system_json)) api_data->system = system_json->valueint;
                    if (cJSON_IsString(osname_json)) {
                        strncpy(api_data->osname, osname_json->valuestring, 99);
                        api_data->osname[99] = '';
                    }
                    
                    cJSON_Delete(json);
                    printf("✅ AUTH SUCCESS: HTTP %ld
", http_status);
                    return API_SUCCESS;
                }
            }
            
            // SPECIFIC AUTH ERROR HANDLING
            if (http_status == 401) {
                fprintf(stderr, "❌ AUTH FAILED: 401 Unauthorized
");
                return API_AUTH_ERROR;
            }
            
            ctx->retry_count++;
            fprintf(stderr, "🔄 Retry %d/%d | HTTP %ld | %s
", 
                   ctx->retry_count, ctx->max_retries, http_status, 
                   curl_easy_strerror(res));
            
            sleep(1 << (ctx->retry_count - 1));
        }
    }
    
use_backup:
    fprintf(stderr, "🔄 RECOVERY: Using backup data
");
    memcpy(api_data, &ctx->backup_data, sizeof(struct os));
    return API_RECOVERY_SUCCESS;
}

void print_status(struct os *data, int status, struct recovery_ctx *ctx) {
    printf("
=== FINAL STATUS ===
");
    switch (status) {
        case API_SUCCESS: printf("✅ FULL SUCCESS
"); break;
        case API_AUTH_ERROR: printf("❌ AUTHENTICATION FAILED
"); break;
        case API_RECOVERY_SUCCESS: printf("🔄 RECOVERY SUCCESS
"); break;
        default: printf("💥 FAILURE: %d
", status);
    }
    printf("Data: Model=%d, System=%d, OS=%s
", 
           data->apimodel, data->system, data->osname);
    printf("==================
");
}

int main() {
    struct os api_data, backup_data;
    struct recovery_ctx ctx;
    struct auth_config auth;
    
    // BACKUP DATA
    backup_data.apimodel = 1;
    backup_data.system = 1;
    strcpy(backup_data.osname, "Lumen");
    
    // AUTH SETUP - CHOOSE ONE:
    init_auth_config(&auth, "apiuser", "apipass");           // Basic Auth
    // set_bearer_token(&auth, "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9...");  // Bearer Token
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    init_recovery_ctx(&ctx, &backup_data);
    init_api_struct(&api_data, &backup_data);
    
    printf("🚀 Starting authenticated API collection...
");
    int status = collect_api_data_with_recovery(&api_data, "http://localhost:8080/api/system-info", 
                                               &ctx, &auth);
    
    print_status(&api_data, status, &ctx);
    curl_global_cleanup();
    return (status == API_SUCCESS) ? 0 : 1;
}
