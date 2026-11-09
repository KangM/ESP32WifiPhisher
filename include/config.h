#ifndef _CONFIG_H
#define _CONFIG_H

#include <esp_system.h>
#include <esp_wifi.h>

/* WIFI CONFIGURATION */
#define DEFAULT_WIFI_SSID           "MagicWifi"
#define DEFAULT_WIFI_PASS           "MagicWifi1234"
#define DEFAULT_WIFI_MAX_CONN       5
#define DEFAULT_WIFI_CHAN           1
#define DEFAULT_WIFI_AUTH           WIFI_AUTH_WPA_WPA2_PSK
#define DEFAULT_WIFI_TX_RATE        WIFI_PHY_RATE_9M

/* ATTACK CHANNEL BEHAVIOUR
 *
 * The board has a single radio, so the SoftAP the dashboard is served on and
 * the channel an attack runs on are the same piece of hardware. There are two
 * ways to get an attack onto a channel the SoftAP is not already using:
 *
 *  1 (set ATTACK_LOCK_AP_CHANNEL to 1)
 *     Re-apply the SoftAP config with the target channel. The radio then sits on
 *     that channel 100% of the time, which is the most effective for deauth
 *     flooding. The cost is that changing the SoftAP channel restarts the
 *     SoftAP interface, so every associated client -- including the phone or
 *     laptop showing the dashboard -- is deauthenticated and has to rescan and
 *     rejoin. csa_count does not help: the CSA element is never sent because
 *     the interface is torn down and re-created.
 *
 *  0 (default)
 *     Leave the SoftAP alone and reach the target channel with
 *     esp_wifi_remain_on_channel(), which parks the radio on the target for a
 *     short window and then hands it back to the SoftAP. The dashboard stays
 *     connected for the whole attack; the trade-off is a duty cycle of roughly
 *     1/4 to 1/2 on the target channel instead of 100%.
 */
#define ATTACK_LOCK_AP_CHANNEL      0


/**
 * @brief Save string value to flash
 * 
 * @param key 
 * @param value 
 */
void save_string_to_nvs(const char* key, const char* value);


/**
 * @brief Read string value from flash
 * 
 * @param key 
 */
esp_err_t read_string_from_nvs(const char* key, char* value);


/**
 * @brief Save int32 to flash
 * 
 * @param key 
 * @param value 
 */
void save_int_to_nvs(const char* key, int32_t value);


/**
 * @brief Read int32_ from Flash
 * 
 * @param key 
 * @param value 
 * @return esp_err_t 
 */
esp_err_t read_int_from_nvs(const char* key, int32_t *value);


#endif