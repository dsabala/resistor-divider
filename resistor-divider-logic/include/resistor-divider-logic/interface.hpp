/**
 * Project: resistor-divider
 * Site: https://github.com/dsabala/resistor-divider
 * License: BSD
 */

#pragma once

enum class SerieType {
  kSerieE3,
  kSerieE6,
  kSerieE12,
  kSerieE24,
  kSerieE48,
  kSerieE96,
  kSerieE192
};

struct SearchCriteria {
  float ratio;
  SerieType serie;
  int results_no;
};

