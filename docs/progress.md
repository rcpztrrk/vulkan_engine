# 📈 PROGRESS TRACKER: Vulkan Engine

## 🚦 Genel Durum
- **Mevcut Odak**: Faz 5 — Physics Engine
- **Tamamlanma**: ~45%
- **Master Plan**: [MASTER_PLAN.md](./MASTER_PLAN.md)

---

## 🛠️ AKTİF GÖREVLER: Faz 5 (Pixel Simulation)

### Adım 5.1: 2D Physics Core
- [ ] Fizik simülasyonunun Z ekseninde kısıtlanması (2D moda geçiş).
- [ ] `RigidBody` içine piksel hassasiyeti (Pixel Snapping) altyapısının eklenmesi.

### Adım 5.2: Pixelator Renderer
- [ ] Low-res Framebuffer kurulumu (örn: 64x64/128x128).
- [ ] Pixelation ve Renk Paleti (Posterization) shader'larının yazılması.
- [ ] ImGui üzerinden "Preview" (önizleme) ekranının geliştirilmesi.

---

## ✅ TAMAMLANANLAR (Log)
- [2026-02-24] Faz 4: ImGui, Fly Camera ve Input Manager tamamlandı.
- [2026-02-20] Faz 3: Model yükleme (OBJ) ve Texture mapping tamamlandı.

---

## 🛡️ GÜVENLİK & OPTİMİZASYON (8-Step Framework)
- [ ] **Check 1**: Physics Memory Audit (Pointer & Resource safety).
- [ ] **Check 2**: Integrator Stability Test (Exploding physics check).
- [ ] **Check 3**: Performance Scan (Physics step profiling).

---
> [!NOTE]
> Teknik detaylı planlar artık Master Plan ve bu dosya içine yedirilmiştir. Ekstra plan dosyalarına gerek yoktur.
