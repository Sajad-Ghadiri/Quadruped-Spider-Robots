static esp_err_t current_color_handler(httpd_req_t *req){
    char*  buf;
    int buf_len = 300;
    if (buf_len > 1) {
        buf = (char*)malloc(buf_len);
        if (httpd_req_get_url_query_str(req,
                    buf, buf_len) == ESP_OK) {
            char param[300], dec_param[300]={0};
        /* Get value of expected key from query string */
            if (httpd_query_key_value(buf,
                          "color", param, 
                          sizeof(param)) == ESP_OK)
               {  Serial.write(param); }           
        }
        free(buf);}
    const char resp[] = "Done";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}
