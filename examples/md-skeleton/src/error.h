/**
 * Calls the crash handler with a custom error message.
 * 
 * @param err Error message to display, newlines (\n) are supported
 */
#define error_fatal(err) _error_other(err, __FILE__, __LINE__)

void _error_fatal(const char *err, const char *file, const uint16_t line);
