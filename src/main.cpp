#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

constexpr int WIDTH = 16;
constexpr int HEIGHT = 16;

NeoPixelBus<NeoGrbFeature, NeoEsp8266DmaWs2812xMethod> leds{WIDTH * HEIGHT};
NeoPixelAnimator animatior{1};
NeoTopology<ColumnMajorAlternatingLayout> topo{WIDTH, HEIGHT};

std::vector<NeoVerticalSpriteSheet<NeoBufferProgmemMethod<NeoGrbFeature>>> sprites {
  // Heart
  {WIDTH, HEIGHT*5, HEIGHT, {}},
    
  // ???
  {WIDTH, HEIGHT*5, HEIGHT, {}},
};


void SpriteSheetAnimation(NeoVerticalSpriteSheet<NeoBufferProgmemMethod<NeoGrbFeature>> sprite, AnimationParam param) {
  uint16_t sprite_index = param.progress * sprite.SpriteCount();
  auto LayoutMap = [](auto x, auto y) {return topo.MapProbe(x, y);};
  sprite.Blt(leds, 0, 0, sprite_index, LayoutMap);
}

void TestAnimation(AnimationParam param) {
  int index = param.progress * 255;
  leds.SetPixelColor(index, RgbColor(255, 128, 128));
  //leds.SetPixelColor(0, RgbColor(128, 128, 256));
}

void setup() {
  leds.Begin();
}

void loop() {
  if (!animatior.IsAnimationActive(0)) {
    //animatior.StartAnimation(0, 10000, [](auto param) {return SpriteSheetAnimation(sprites.at(rand() % sprites.size()), param);});
    animatior.StartAnimation(0, 10000, TestAnimation);
  }

  animatior.UpdateAnimations();
  leds.Show();
}