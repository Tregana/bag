#include <bag>
#include <iostream>
#include <vector>
int _Volumes_build_bag_test_bag(int, char*[]) noexcept
{
  using x = const std::vector<int>;
  tregana::bag<x> b;
  tregana::bag_context c;
  x v0{0, 1, 2, 3}, v1{0, 1, 2}, v2{0, 1};

  b.insert(c, v0)
   .insert(c, v1)
   .insert(c, v2);
  {
    const auto h0{b.contains(v1)};
    std::cout << h0.first << '\t' << h0.second << std::endl;
  }
  b.remove(c, v1);
  {
    const auto h0{b.contains(v1)};
    std::cout << h0.first << '\t' << h0.second << std::endl;
  }
  x v3{*b.consume(c)};
  if (v3.size() != v0.size() or ! std::equal(v3.begin(), v3.end(), v0.begin()))
    return 1;

  return 0;
}
