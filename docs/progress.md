# PROGRESS TRACKER: Vulkan Engine

## Genel Durum
- Mevcut Odak: Faz 6A2 - Material System & Faz 5.5 - Animation Bridge
- Tamamlanma: ~68%
- Master Plan: [MASTER_PLAN.md](./MASTER_PLAN.md)

---

## AKTIF GOREVLER: Faz 5.5 (Animation-to-Bake Bridge)

### Adim 5.5.1: Animation Pipeline
- [ ] Skeletal animation clip oynatma altyapisini ekle.
- [ ] Kemiksiz modeller icin keyframe/transform timeline sistemi ekle.
- [ ] Animation state machine (idle/run/attack vb.) temel gecislerini kur.

### Adim 5.5.2: Shot Authoring
- [ ] Kamera presetleri (front/side/isometric) tanimla.
- [ ] Isik presetleri olustur (sabit, tekrar uretilebilir).
- [ ] Animasyon + fizik baslangic snapshot sistemi ekle.

### Adim 5.5.3: Deterministic Playback
- [ ] Fixed-step playback araclari (play/pause/step/reset) ekle.
- [ ] Seed/snapshot ile tekrar uretilebilir simulasyon akisini dogrula.
- [ ] Frame-range capture hazirligi (or. 0-47) ekle.

### Adim 5.5.4: Bake-Oncesi Stylization
- [ ] Pixel snap kurallarini kamera/obje tarafinda tanimla.
- [ ] Palette limiter + preview akis taslagini olustur.
- [ ] Alpha/background davranisini spritesheet bake icin netlestir.

---

## SIRADAKI FAZ: Faz 6 (The Baker)
- [ ] Render-to-Texture (offscreen rendering) altyapisi.
- [ ] `stb_image_write` ile PNG frame export.
- [ ] Spritesheet atlas packing + Godot uyumlu JSON metadata.

---

## TAMAMLANANLAR (Log)
- [2026-02-28] Faz 6A1: Blinn-Phong Lighting & UBO Alignment (std140) tamamlandi.
- [2026-02-28] Faz 5: Physics Engine (Collision Detection & Response) tamamlandi.
- [2026-02-24] Faz 4: ImGui, Fly Camera ve Input Manager tamamlandi.
- [2026-02-20] Faz 3: Model yukleme (OBJ) ve Texture mapping tamamlandi.

---

## GUVENLIK & OPTIMIZASYON (8-Step Framework)
- [ ] Check 1: Physics Memory Audit (Pointer & Resource safety).
- [ ] Check 2: Integrator Stability Test (Exploding physics check).
- [ ] Check 3: Performance Scan (Physics step profiling).
- [ ] Check 4: Capture Pipeline Audit (Render target lifetime + IO failure handling).

---
> [!NOTE]
> Teknik detayli planlar Master Plan ve bu dosyada tutulur.
> Faz degisimi oldugunda once bu iki dosya birlikte guncellenir.
