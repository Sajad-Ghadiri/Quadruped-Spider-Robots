void startCameraServer(){
httpd_config_t config = HTTPD_DEFAULT_CONFIG();
httpd_uri_t index_uri = {
  .uri     = "/",  .method  = HTTP_GET,
  .handler   = index_handler, .user_ctx  = NULL
    };
httpd_uri_t capture_uri = {
  .uri     = "/capture",  .method  = HTTP_GET,
  .handler = capture_handler, .user_ctx  = NULL
    };
httpd_uri_t stream_uri = {
  .uri     = "/stream",  .method  = HTTP_GET,
  .handler = stream_handler, .user_ctx  = NULL
    };
httpd_uri_t current_color_uri = {
  .uri     = "/currentColor",  .method  = HTTP_GET,
  .handler = current_color_handler, .user_ctx  = NULL
    };
  
