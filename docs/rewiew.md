# Proje İnceleme Notları

## Genel Durum
- Proje modüler: `core` (uygulama döngüsü), `renderer` (Vulkan + ImGui), `physics` (basit rigid body), `tools` (profiler/inspector).
- CMake + vcpkg kurulumu temiz; bağımlılıklar doğru tanımlı.
- ECS yaklaşımı (`EnTT`) ve sabit fizik adımı (`fixedDt`) iyi bir temel.

## Kritik Bulgular
1. Pencere başlatma hatasında sessiz devam riski var. `glfwInit`/`glfwCreateWindow` başarısızsa sadece `return` ediliyor; bu durumda uygulama null pencereyle rendereri başlatabilir (çökme riski).
   - `src/core/Window.cpp:9`
   - `src/core/Window.cpp:17`

2. Present tarafında swapchain yenileme eksik bırakılmış (`TBD`). `vkQueuePresentKHR` sonucu `OUT_OF_DATE/SUBOPTIMAL` olduğunda yeniden oluşturma çağrılmıyor.
   - `src/renderer/VulkanRenderer.cpp:1406`
   - `src/renderer/VulkanRenderer.cpp:1460`

3. Profilerde sıfıra bölme riski var (`deltaTime == 0` olursa).
   - `src/tools/Profiler.cpp:13`

## Orta Seviye Riskler
- Test altyapısı pratikte yok (`tests/` boş, `add_test/ctest` yok). Regresyon riski yüksek.
- Fizik senkronizasyonu her adımda `Transform -> RigidBody` yapıyor; harici teleport için faydalı ama ileride kuvvet/otorite çatışması yaratabilir.
  - `src/physics/PhysicsEngine.cpp:21`
- Shader/model path’leri göreli; çalışma dizini bağımlılığı var.
  - `src/renderer/VulkanRenderer.cpp:655`
  - `src/renderer/VulkanRenderer.cpp:1140`

## Artılar
- Init/Shutdown sırası genel olarak düzenli.
- ImGui debug araçları (Profiler + EntityInspector) geliştirme hızını artırır.
- Dokümantasyon roadmap odaklı ve net.

## Hızlı Öncelik Önerisi
1. `Window` hatalarında exception fırlatıp güvenli fail-fast.
2. Present sonrası swapchain recreate akışını tamamla.
3. Profiler’da `deltaTime` guard ekle.
4. En azından smoke + physics unit testleri ekle.

## Not
Çalışma ağacında mevcut değişiklikler vardı:
- `src/physics/RigidBody.h` modified
- `docs/` untracked
