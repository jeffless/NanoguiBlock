/*
    src/imageview.cpp -- Simple widget which shows an image that was
    previously uploaded to the graphics card

    NanoGUI was developed by Wenzel Jakob <wenzel@inf.ethz.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

NAMESPACE_BEGIN (nanogui)

ImageView::ImageView (Widget * parent, int img)
   : Widget (parent), mImage (img) {}

ivec2 ImageView::preferredSize (NVGcontext * ctx) const
{
   if (!mImage)
      return ivec2 (0, 0);
   int w, h;
   nvgImageSize (ctx, mImage, &w, &h);
   return ivec2 (w, h);
}

void ImageView::draw (NVGcontext * ctx)
{
   if (!mImage)
      return;
   ivec2 p = mPos;
   ivec2 s = Widget::size();
   int w, h;
   nvgImageSize (ctx, mImage, &w, &h);
   if (s.x < w)
   {
      h = (int) std::round (h * (float) s.x / w);
      w = s.x;
   }
   if (s.y < h)
   {
      w = (int) std::round (w * (float) s.y / h);
      h = s.y;
   }
   NVGpaint imgPaint = nvgImagePattern (ctx, p.x, p.y, w, h, 0, mImage, 1.0);
   nvgBeginPath (ctx);
   nvgRect (ctx, p.x, p.y, w, h);
   nvgFillPaint (ctx, imgPaint);
   nvgFill (ctx);
}

NAMESPACE_END (nanogui)