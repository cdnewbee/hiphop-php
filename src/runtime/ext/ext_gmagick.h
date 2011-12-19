/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef __EXT_GMAGICK_H__
#define __EXT_GMAGICK_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <runtime/base/base_includes.h>
#include <util/exception.h>
#include <string>

struct _PixelWand;
typedef struct _PixelWand PixelWand;

struct _MagickWand;
typedef struct _MagickWand MagickWand;
namespace HPHP {
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// class GmagickPixel

FORWARD_DECLARE_CLASS_BUILTIN(GmagickPixel);
class c_GmagickPixel : public ExtObjectData {
 public:
  DECLARE_CLASS(GmagickPixel, GmagickPixel, ObjectData)

  // need to implement
  public: c_GmagickPixel(const ObjectStaticCallbacks *cb = &cw_GmagickPixel);
  public: ~c_GmagickPixel();
  public: void t___construct(CStrRef color = null_string);
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_GmagickPixel *create(String color = null_string);
  static const ClassPropTable os_prop_table;
   public: 
     PixelWand *get_PixelWand();
   private:
     PixelWand *pixel_wand;
};
extern const int q_Gmagick$$FILTER_UNDEFINED;
extern const int q_Gmagick$$COMPOSITE_DEFAULT;
extern const int q_Gmagick$$COMPOSITE_UNDEFINED;
extern const int q_Gmagick$$COMPOSITE_NO;
extern const int q_Gmagick$$COMPOSITE_ADD;
extern const int q_Gmagick$$COMPOSITE_ATOP;
extern const int q_Gmagick$$COMPOSITE_BUMPMAP;
extern const int q_Gmagick$$COMPOSITE_CLEAR;
extern const int q_Gmagick$$COMPOSITE_COLORIZE;
extern const int q_Gmagick$$COMPOSITE_COPYBLACK;
extern const int q_Gmagick$$COMPOSITE_COPYBLUE;
extern const int q_Gmagick$$COMPOSITE_COPY;
extern const int q_Gmagick$$COMPOSITE_COPYCYAN;
extern const int q_Gmagick$$COMPOSITE_COPYGREEN;
extern const int q_Gmagick$$COMPOSITE_COPYMAGENTA;
extern const int q_Gmagick$$COMPOSITE_COPYOPACITY;
extern const int q_Gmagick$$COMPOSITE_COPYRED;
extern const int q_Gmagick$$COMPOSITE_COPYYELLOW;
extern const int q_Gmagick$$COMPOSITE_DARKEN;
extern const int q_Gmagick$$COMPOSITE_DIFFERENCE;
extern const int q_Gmagick$$COMPOSITE_DISPLACE;
extern const int q_Gmagick$$COMPOSITE_DISSOLVE;
extern const int q_Gmagick$$COMPOSITE_HUE;
extern const int q_Gmagick$$COMPOSITE_IN;
extern const int q_Gmagick$$COMPOSITE_LIGHTEN;
extern const int q_Gmagick$$COMPOSITE_LUMINIZE;
extern const int q_Gmagick$$COMPOSITE_MINUS;
extern const int q_Gmagick$$COMPOSITE_MODULATE;
extern const int q_Gmagick$$COMPOSITE_MULTIPLY;
extern const int q_Gmagick$$COMPOSITE_OUT;
extern const int q_Gmagick$$COMPOSITE_OVER;
extern const int q_Gmagick$$COMPOSITE_OVERLAY;
extern const int q_Gmagick$$COMPOSITE_PLUS;
extern const int q_Gmagick$$COMPOSITE_REPLACE;
extern const int q_Gmagick$$COMPOSITE_SATURATE;
extern const int q_Gmagick$$COMPOSITE_SCREEN;
extern const int q_Gmagick$$COMPOSITE_SUBTRACT;
extern const int q_Gmagick$$COMPOSITE_THRESHOLD;
extern const int q_Gmagick$$COMPOSITE_XOR;
extern const int q_Gmagick$$MONTAGEMODE_FRAME;
extern const int q_Gmagick$$MONTAGEMODE_UNFRAME;
extern const int q_Gmagick$$MONTAGEMODE_CONCATENATE;
extern const int q_Gmagick$$STYLE_NORMAL;
extern const int q_Gmagick$$STYLE_ITALIC;
extern const int q_Gmagick$$STYLE_OBLIQUE;
extern const int q_Gmagick$$STYLE_ANY;
extern const int q_Gmagick$$FILTER_UNDEFINED;
extern const int q_Gmagick$$FILTER_POINT;
extern const int q_Gmagick$$FILTER_BOX;
extern const int q_Gmagick$$FILTER_TRIANGLE;
extern const int q_Gmagick$$FILTER_HERMITE;
extern const int q_Gmagick$$FILTER_HANNING;
extern const int q_Gmagick$$FILTER_HAMMING;
extern const int q_Gmagick$$FILTER_BLACKMAN;
extern const int q_Gmagick$$FILTER_GAUSSIAN;
extern const int q_Gmagick$$FILTER_QUADRATIC;
extern const int q_Gmagick$$FILTER_CUBIC;
extern const int q_Gmagick$$FILTER_CATROM;
extern const int q_Gmagick$$FILTER_MITCHELL;
extern const int q_Gmagick$$FILTER_LANCZOS;
extern const int q_Gmagick$$FILTER_BESSEL;
extern const int q_Gmagick$$FILTER_SINC;
extern const int q_Gmagick$$IMGTYPE_UNDEFINED;
extern const int q_Gmagick$$IMGTYPE_BILEVEL;
extern const int q_Gmagick$$IMGTYPE_GRAYSCALE;
extern const int q_Gmagick$$IMGTYPE_GRAYSCALEMATTE;
extern const int q_Gmagick$$IMGTYPE_PALETTE;
extern const int q_Gmagick$$IMGTYPE_PALETTEMATTE;
extern const int q_Gmagick$$IMGTYPE_TRUECOLOR;
extern const int q_Gmagick$$IMGTYPE_TRUECOLORMATTE;
extern const int q_Gmagick$$IMGTYPE_COLORSEPARATION;
extern const int q_Gmagick$$IMGTYPE_COLORSEPARATIONMATTE;
extern const int q_Gmagick$$IMGTYPE_OPTIMIZE;
extern const int q_Gmagick$$RESOLUTION_UNDEFINED;
extern const int q_Gmagick$$RESOLUTION_PIXELSPERINCH;
extern const int q_Gmagick$$RESOLUTION_PIXELSPERCENTIMETER;
extern const int q_Gmagick$$COMPRESSION_UNDEFINED;
extern const int q_Gmagick$$COMPRESSION_NO;
extern const int q_Gmagick$$COMPRESSION_BZIP;
extern const int q_Gmagick$$COMPRESSION_FAX;
extern const int q_Gmagick$$COMPRESSION_GROUP4;
extern const int q_Gmagick$$COMPRESSION_JPEG;
extern const int q_Gmagick$$COMPRESSION_LOSSLESSJPEG;
extern const int q_Gmagick$$COMPRESSION_LZW;
extern const int q_Gmagick$$COMPRESSION_RLE;
extern const int q_Gmagick$$COMPRESSION_ZIP;
extern const int q_Gmagick$$PAINT_POINT;
extern const int q_Gmagick$$PAINT_REPLACE;
extern const int q_Gmagick$$PAINT_FLOODFILL;
extern const int q_Gmagick$$PAINT_FILLTOBORDER;
extern const int q_Gmagick$$PAINT_RESET;
extern const int q_Gmagick$$GRAVITY_NORTHWEST;
extern const int q_Gmagick$$GRAVITY_NORTH;
extern const int q_Gmagick$$GRAVITY_NORTHEAST;
extern const int q_Gmagick$$GRAVITY_WEST;
extern const int q_Gmagick$$GRAVITY_CENTER;
extern const int q_Gmagick$$GRAVITY_EAST;
extern const int q_Gmagick$$GRAVITY_SOUTHWEST;
extern const int q_Gmagick$$GRAVITY_SOUTH;
extern const int q_Gmagick$$GRAVITY_SOUTHEAST;
extern const int q_Gmagick$$STRETCH_NORMAL;
extern const int q_Gmagick$$STRETCH_ULTRACONDENSED;
extern const int q_Gmagick$$STRETCH_CONDENSED;
extern const int q_Gmagick$$STRETCH_SEMICONDENSED;
extern const int q_Gmagick$$STRETCH_SEMIEXPANDED;
extern const int q_Gmagick$$STRETCH_EXPANDED;
extern const int q_Gmagick$$STRETCH_EXTRAEXPANDED;
extern const int q_Gmagick$$STRETCH_ULTRAEXPANDED;
extern const int q_Gmagick$$STRETCH_ANY;
extern const int q_Gmagick$$ALIGN_UNDEFINED;
extern const int q_Gmagick$$ALIGN_LEFT;
extern const int q_Gmagick$$ALIGN_CENTER;
extern const int q_Gmagick$$ALIGN_RIGHT;
extern const int q_Gmagick$$DECORATION_NO;
extern const int q_Gmagick$$DECORATION_UNDERLINE;
extern const int q_Gmagick$$DECORATION_OVERLINE;
extern const int q_Gmagick$$DECORATION_LINETROUGH;
extern const int q_Gmagick$$NOISE_UNIFORM;
extern const int q_Gmagick$$NOISE_GAUSSIAN;
extern const int q_Gmagick$$NOISE_MULTIPLICATIVEGAUSSIAN;
extern const int q_Gmagick$$NOISE_IMPULSE;
extern const int q_Gmagick$$NOISE_LAPLACIAN;
extern const int q_Gmagick$$NOISE_POISSON;
extern const int q_Gmagick$$CHANNEL_UNDEFINED;
extern const int q_Gmagick$$CHANNEL_RED;
extern const int q_Gmagick$$CHANNEL_GRAY;
extern const int q_Gmagick$$CHANNEL_CYAN;
extern const int q_Gmagick$$CHANNEL_GREEN;
extern const int q_Gmagick$$CHANNEL_MAGENTA;
extern const int q_Gmagick$$CHANNEL_BLUE;
extern const int q_Gmagick$$CHANNEL_YELLOW;
extern const int q_Gmagick$$CHANNEL_OPACITY;
extern const int q_Gmagick$$CHANNEL_MATTE;
extern const int q_Gmagick$$CHANNEL_BLACK;
extern const int q_Gmagick$$CHANNEL_INDEX;
extern const int q_Gmagick$$CHANNEL_ALL;
extern const int q_Gmagick$$METRIC_UNDEFINED;
extern const int q_Gmagick$$METRIC_MEANABSOLUTEERROR;
extern const int q_Gmagick$$METRIC_MEANSQUAREERROR;
extern const int q_Gmagick$$METRIC_PEAKABSOLUTEERROR;
extern const int q_Gmagick$$METRIC_PEAKSIGNALTONOISERATIO;
extern const int q_Gmagick$$METRIC_ROOTMEANSQUAREDERROR;
extern const int q_Gmagick$$PIXEL_CHAR;
extern const int q_Gmagick$$PIXEL_DOUBLE;
extern const int q_Gmagick$$PIXEL_FLOAT;
extern const int q_Gmagick$$PIXEL_INTEGER;
extern const int q_Gmagick$$PIXEL_LONG;
extern const int q_Gmagick$$PIXEL_SHORT;
extern const int q_Gmagick$$COLORSPACE_UNDEFINED;
extern const int q_Gmagick$$COLORSPACE_RGB;
extern const int q_Gmagick$$COLORSPACE_GRAY;
extern const int q_Gmagick$$COLORSPACE_TRANSPARENT;
extern const int q_Gmagick$$COLORSPACE_OHTA;
extern const int q_Gmagick$$COLORSPACE_LAB;
extern const int q_Gmagick$$COLORSPACE_XYZ;
extern const int q_Gmagick$$COLORSPACE_YCBCR;
extern const int q_Gmagick$$COLORSPACE_YCC;
extern const int q_Gmagick$$COLORSPACE_YIQ;
extern const int q_Gmagick$$COLORSPACE_YPBPR;
extern const int q_Gmagick$$COLORSPACE_YUV;
extern const int q_Gmagick$$COLORSPACE_CMYK;
extern const int q_Gmagick$$COLORSPACE_SRGB;
extern const int q_Gmagick$$COLORSPACE_HSL;
extern const int q_Gmagick$$COLORSPACE_HWB;
extern const int q_Gmagick$$VIRTUALPIXELMETHOD_UNDEFINED;
extern const int q_Gmagick$$VIRTUALPIXELMETHOD_CONSTANT;
extern const int q_Gmagick$$VIRTUALPIXELMETHOD_EDGE;
extern const int q_Gmagick$$VIRTUALPIXELMETHOD_MIRROR;
extern const int q_Gmagick$$VIRTUALPIXELMETHOD_TILE;
extern const int q_Gmagick$$PREVIEW_UNDEFINED;
extern const int q_Gmagick$$PREVIEW_ROTATE;
extern const int q_Gmagick$$PREVIEW_SHEAR;
extern const int q_Gmagick$$PREVIEW_ROLL;
extern const int q_Gmagick$$PREVIEW_HUE;
extern const int q_Gmagick$$PREVIEW_SATURATION;
extern const int q_Gmagick$$PREVIEW_BRIGHTNESS;
extern const int q_Gmagick$$PREVIEW_GAMMA;
extern const int q_Gmagick$$PREVIEW_SPIFF;
extern const int q_Gmagick$$PREVIEW_DULL;
extern const int q_Gmagick$$PREVIEW_GRAYSCALE;
extern const int q_Gmagick$$PREVIEW_QUANTIZE;
extern const int q_Gmagick$$PREVIEW_DESPECKLE;
extern const int q_Gmagick$$PREVIEW_REDUCENOISE;
extern const int q_Gmagick$$PREVIEW_ADDNOISE;
extern const int q_Gmagick$$PREVIEW_SHARPEN;
extern const int q_Gmagick$$PREVIEW_BLUR;
extern const int q_Gmagick$$PREVIEW_THRESHOLD;
extern const int q_Gmagick$$PREVIEW_EDGEDETECT;
extern const int q_Gmagick$$PREVIEW_SPREAD;
extern const int q_Gmagick$$PREVIEW_SOLARIZE;
extern const int q_Gmagick$$PREVIEW_SHADE;
extern const int q_Gmagick$$PREVIEW_RAISE;
extern const int q_Gmagick$$PREVIEW_SEGMENT;
extern const int q_Gmagick$$PREVIEW_SWIRL;
extern const int q_Gmagick$$PREVIEW_IMPLODE;
extern const int q_Gmagick$$PREVIEW_WAVE;
extern const int q_Gmagick$$PREVIEW_OILPAINT;
extern const int q_Gmagick$$PREVIEW_CHARCOALDRAWING;
extern const int q_Gmagick$$PREVIEW_JPEG;
extern const int q_Gmagick$$RENDERINGINTENT_UNDEFINED;
extern const int q_Gmagick$$RENDERINGINTENT_SATURATION;
extern const int q_Gmagick$$RENDERINGINTENT_PERCEPTUAL;
extern const int q_Gmagick$$RENDERINGINTENT_ABSOLUTE;
extern const int q_Gmagick$$RENDERINGINTENT_RELATIVE;
extern const int q_Gmagick$$INTERLACE_UNDEFINED;
extern const int q_Gmagick$$INTERLACE_NO;
extern const int q_Gmagick$$INTERLACE_LINE;
extern const int q_Gmagick$$INTERLACE_PLANE;
extern const int q_Gmagick$$INTERLACE_PARTITION;
extern const int q_Gmagick$$FILLRULE_UNDEFINED;
extern const int q_Gmagick$$FILLRULE_EVENODD;
extern const int q_Gmagick$$FILLRULE_NONZERO;
extern const int q_Gmagick$$PATHUNITS_USERSPACE;
extern const int q_Gmagick$$PATHUNITS_USERSPACEONUSE;
extern const int q_Gmagick$$PATHUNITS_OBJECTBOUNDINGBOX;
extern const int q_Gmagick$$LINECAP_UNDEFINED;
extern const int q_Gmagick$$LINECAP_BUTT;
extern const int q_Gmagick$$LINECAP_ROUND;
extern const int q_Gmagick$$LINECAP_SQUARE;
extern const int q_Gmagick$$LINEJOIN_UNDEFINED;
extern const int q_Gmagick$$LINEJOIN_MITER;
extern const int q_Gmagick$$LINEJOIN_ROUND;
extern const int q_Gmagick$$LINEJOIN_BEVEL;
extern const int q_Gmagick$$RESOURCETYPE_UNDEFINED;
extern const int q_Gmagick$$RESOURCETYPE_AREA;
extern const int q_Gmagick$$RESOURCETYPE_DISK;
extern const int q_Gmagick$$RESOURCETYPE_FILE;
extern const int q_Gmagick$$RESOURCETYPE_MAP;
extern const int q_Gmagick$$RESOURCETYPE_MEMORY;
extern const int q_Gmagick$$DISPOSE_UNDEFINED;
extern const int q_Gmagick$$DISPOSE_NONE;
extern const int q_Gmagick$$DISPOSE_BACKGROUND;
extern const int q_Gmagick$$DISPOSE_PREVIOUS;

///////////////////////////////////////////////////////////////////////////////
// class Gmagick

FORWARD_DECLARE_CLASS_BUILTIN(Gmagick);
class c_Gmagick : public ExtObjectData, public Sweepable {
 public:
  DECLARE_CLASS(Gmagick, Gmagick, ObjectData)

  // need to implement
  public: c_Gmagick(const ObjectStaticCallbacks *cb = &cw_Gmagick);
  public: ~c_Gmagick();
  public: void t___construct();
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);
  public: void t_destroy();
  DECLARE_METHOD_INVOKE_HELPERS(destroy);
  public: String t_getcopyright();
  DECLARE_METHOD_INVOKE_HELPERS(getcopyright);
  public: Object t_readimageblob(CStrRef blob, CStrRef filename);
  DECLARE_METHOD_INVOKE_HELPERS(readimageblob);
  public: String t_getimageblob();
  DECLARE_METHOD_INVOKE_HELPERS(getimageblob);
  public: String t_getimagefilename();
  DECLARE_METHOD_INVOKE_HELPERS(getimagefilename);
  public: int64 t_getimagetype();
  DECLARE_METHOD_INVOKE_HELPERS(getimagetype);
  public: String t_getimageformat();
  DECLARE_METHOD_INVOKE_HELPERS(getimageformat);
  public: int64 t_getimagecolorspace();
  DECLARE_METHOD_INVOKE_HELPERS(getimagecolorspace);
  public: String t_getimageprofile(CStrRef profile);
  DECLARE_METHOD_INVOKE_HELPERS(getimageprofile);
  public: Object t_profileimage(CStrRef name, CStrRef profile);
  DECLARE_METHOD_INVOKE_HELPERS(profileimage);
  public: Object t_setcompressionquality(int64 quality);
  DECLARE_METHOD_INVOKE_HELPERS(setcompressionquality);
  public: Object t_readimage(CStrRef filename);
  DECLARE_METHOD_INVOKE_HELPERS(readimage);
  public: int64 t_getimagewidth();
  DECLARE_METHOD_INVOKE_HELPERS(getimagewidth);
  public: int64 t_getimageheight();
  DECLARE_METHOD_INVOKE_HELPERS(getimageheight);
  public: Object t_resizeimage(int64 columns, int64 rows, int64 filter_type, double blur, bool fit = false);
  DECLARE_METHOD_INVOKE_HELPERS(resizeimage);
  public: Object t_rotateimage(CObjRef background, double degrees);
  DECLARE_METHOD_INVOKE_HELPERS(rotateimage);
  public: Object t_setimageformat(CStrRef format);
  DECLARE_METHOD_INVOKE_HELPERS(setimageformat);
  public: Object t_cropimage(int64 width, int64 height, int64 x, int64 y);
  DECLARE_METHOD_INVOKE_HELPERS(cropimage);
  public: Object t_writeimage(CStrRef filename, bool all_frames = false);
  DECLARE_METHOD_INVOKE_HELPERS(writeimage);
  public: Object t_borderimage(CObjRef bordercolor, int64 width, int64 height);
  DECLARE_METHOD_INVOKE_HELPERS(borderimage);

  // implemented by HPHP
  public: c_Gmagick *create();
  static const ClassPropTable os_prop_table;

 private:
  void checkResult(int result);
  void checkNotEmpty(); 
  void checkHasFormat();
  void throwException(const char * magick_message, int magick_severity);
  bool adjust_dimensions(bool bestfit, long desired_width, long desired_height, long *new_width, long *new_height);
  MagickWand *magick_wand;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_GMAGICK_H__