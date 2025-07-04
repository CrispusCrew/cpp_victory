#include "static_files_list.h"
#include "cache.h"
#include "../utils.h"

#include <stdexcept>

namespace core
{

  Cache::result Cache::Get(const std::string& key) const
  {
    if (auto it = cache_.find(key); it != cache_.end())
    {
      return {true, it->second};
    }

    return {false, ""};
  }

  Cache::status Cache::Add(const std::string& key, const std::string& data)
  {
    if (auto it = cache_.find(key); it != cache_.end())
    {
      return false;
    }

    cache_[key] = data;
    return true;
  }

void InitCache(Cache& cache)
{
  for (size_t i = 0; i < static_dir::size; ++i)
  {
    const std::string path = static_dir::files[i];
    std::string data;
    if (core::utils::StaticContent::GetFile(path, data))
    {
      cache.Add(path, data);
    }
    else
    {
      throw std::runtime_error("Can't find file " + path + " in cache");
    }
  }
}

} // namespace core
