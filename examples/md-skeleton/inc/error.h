/**
 * If you have a custom memory allocator, call this when it is not able to
 * allocate the requested amount of space.
 */
#define error_oom() _error_oom(__FILE__, __LINE__)

/**
 * Calls the crash handler with a custom error message.
 * 
 * @param err Error message to display, newlines (\n) are supported
 */
#define error_fatal(err) _error_other(err, __FILE__, __LINE__)

void _error_oom(const char* file, const uint16_t line);
void _error_fatal(const char *err, const char *file, const uint16_t line);
