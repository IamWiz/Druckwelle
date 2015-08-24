
#include "../WebMapService.h"

using namespace std;

namespace dw
{
namespace Layers
{
	const astring LayerName = "ExampleLayer";
	const string LayerTitle = dwTEXT("Example Layer showing how to implement the basics for your own layer");

	class CircleTestLayer : public WebMapService::Layer
	{
		virtual ~CircleTestLayer() override {};

	public:

		virtual const char* GetName() const override
		{
			return LayerName.c_str();
		}

		virtual const char_t* GetTitle() const override
		{
			return LayerTitle.c_str();
		}

		virtual const vector<DataType>& GetSuppordetFormats() const override
		{
			static const vector<DataType> SuppordetFormats = { DT_RGBA8 };
			return SuppordetFormats;
		}

		template<typename T>
		HandleGetMapRequestResult HandleGetMapRequest(const WebMapService::GetMapRequest& gmr, T* data, T circleColor)
		{
			memset(data, 0, sizeof(T) * gmr.width * gmr.height);

			const int numPixels = gmr.width * 3;
			for (size_t p = 0; p < numPixels; p++)
			{
				int x = (int)((gmr.width + cos((double)p) * gmr.width) * 0.5);
				int y = (int)((gmr.height + sin((double)p) * gmr.height) * 0.5);

				data[y * gmr.width + x] = circleColor;
			}

			return HGMRR_OK;
		}

		virtual HandleGetMapRequestResult HandleGetMapRequest(const WebMapService::GetMapRequest& gmr, u8* data) override
		{
			switch (gmr.dataType)
			{
			case DT_RGBA8:
				return HandleGetMapRequest<u32>(gmr, (u32*)data, 0xFF0000FF);
			default:
				return HGMRR_InvalidFormat;
			}
		}
	};

	IMPLEMENT_WEBMAPSERVICE_LAYER(CircleTestLayer, LayerName, LayerTitle);
}
}