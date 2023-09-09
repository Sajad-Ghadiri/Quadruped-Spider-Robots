  // some config set up here  
  Serial.printf("Starting web server on port: '%d'\n",
  config.server_port);
if (httpd_start(&camera_httpd, &config) == ESP_OK) {
  httpd_register_uri_handler(camera_httpd, &index_uri);
  httpd_register_uri_handler(camera_httpd, &stream_uri);
  httpd_register_uri_handler(camera_httpd, &capture_uri);
  httpd_register_uri_handler(camera_httpd, &current_color_uri);
  }
  config.server_port += 1;  config.ctrl_port += 1;
  Serial.printf("Starting stream server on port: '%d'\n",
  config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
      httpd_register_uri_handler(stream_httpd, &stream_uri);
    }
 }
