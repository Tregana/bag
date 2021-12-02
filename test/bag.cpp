#include <bag>
#include <iostream>
#include <vector>
int _Volumes_build_bag_test_bag(int, char*[]) noexcept
{
  tregana::bag_context c;//one per thread
  {
    tregana::bag<const std::vector<int>> b;
    const std::vector<int> v0{0, 1, 2, 3}, v1{0, 1, 2}, v2{0, 1};
    b.insert(c, v0)
     .insert(c, v1)
     .insert(c, v2);
    if (const auto h{b.contains(v1)}; h.second < h.first)
      return 1;
    if (const auto h{b.remove(c, v1).contains(v1)}; h.first != h.second)
      return 1;
    if (const auto v{*b.consume(c)}; v.size() != v0.size() or ! std::equal(v.begin(), v.end(), v0.begin()))
      return 1;

    tregana::bag<const std::vector<int>> a;
    a.insert(c, {0, 1, 2, 3, 4});

    size_t s{a.size()+b.size()};
    if (auto&& m{std::move(a)+std::move(b)}; m.size() != s)
      return 1;
  }
  {
    tregana::bag<const std::vector<int>> b, a, x;
    const std::vector<int> v{0, 1, 2, 3, 4}, w{0, 1}, z{0, 2},
      v0{}, v1{0}, v2{0, 1, 2}, v3{0, 1, 2, 3}, v4{0, 1, 2, 3, 4, 5};
    a.insert(c, v).insert(c, w);
    x.insert(c, z);
    b.insert(c, v0)
     .insert(c, v1)
     .insert(c, w)
     .insert(c, v2)
     .insert(c, v3)
     .insert(c, v)
     .insert(c, v4);
    const auto s{b.size() - a.size()};
    c.size -= (b -= a).first.size;
    if (b.size() != s)
      return 1;
    auto r{b -= x};
    if (r.first.size != 0 or b.size() != s)
      return 1;
  }

  return 0;
}
