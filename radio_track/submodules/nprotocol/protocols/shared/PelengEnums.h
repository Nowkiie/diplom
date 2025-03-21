#pragma once
#include <cstdint>

namespace peleng_enums
{

enum class rpp_formation : int32_t
{
    base = 0,
    mobile = 1,
    marine = 2,
};

enum class rpa_type : int32_t
{
    automatic = 0,
    manual
};

enum class peleng_error : int32_t
{
    not_found = 1,     // Не обнаружено (НО)
    transport_error,   // Ошибка передачи (ОКС)
    service_error,     // Ошибка службы пеленгования (НПК)
    pelengator_error,  // Ошибка пеленгатора (РЗ, ОРП, НДК)
};

enum class place_type : int32_t
{
    triangular = 0,  // Триангулационное
    single_point,    // Одноточечное
};

}  // namespace peleng_enums
