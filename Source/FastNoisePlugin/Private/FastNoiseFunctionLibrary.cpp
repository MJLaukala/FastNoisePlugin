// Copyright(c) 2021 Matthew Laukala
//
// Copyright 2018 Yaki Studios, Inc. All Rights Reserved.
//
// MIT License
//
// Copyright(c) 2017 Jordan Peck
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "FastNoiseFunctionLibrary.h"

const FIntPoint GGradient2DLut[] =
{
	{-1,-1},{1,-1},{-1,1},{1,1},
	{0,-1},{-1,0},{0,1},{1,0}
};

const FIntVector GGradient3DLut[] =
{
	{1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
	{1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
	{0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}
};

const FIntVector4 GGradient4DLut[] =
{
	{0,1,1,1},{0,1,1,-1},{0,1,-1,1},{0,1,-1,-1},
	{0,-1,1,1},{0,-1,1,-1},{0,-1,-1,1},{0,-1,-1,-1},
	{1,0,1,1},{1,0,1,-1},{1,0,-1,1},{1,0,-1,-1},
	{-1,0,1,1},{-1,0,1,-1},{-1,0,-1,1},{-1,0,-1,-1},
	{1,1,0,1},{1,1,0,-1},{1,-1,0,1},{1,-1,0,-1},
	{-1,1,0,1},{-1,1,0,-1},{-1,-1,0,1},{-1,-1,0,-1},
	{1,1,1,0},{1,1,-1,0},{1,-1,1,0},{1,-1,-1,0},
	{-1,1,1,0},{-1,1,-1,0},{-1,-1,1,0},{-1,-1,-1,0}
};

const FVector2D GCell2D[] =
{
	{-0.6440658039f,0.7649700911f},{-0.0802807872f,0.9967722885f},{0.9983546168f,0.0573416003f},{0.9869492062f,-0.1610318741f},{0.9284746418f,0.3713957990f},{0.6051097552f,-0.7961420628f},{-0.7941674040f,0.6076990492f},{-0.3488667991f,-0.9371723195f},{-0.9431365260f,0.3324056156f},{-0.9968171318f,0.0797220533f},{0.8740961579f,-0.4857529277f},{0.1421139764f,-0.9898503007f},{0.4282553608f,0.9036577593f},{-0.9986665833f,0.0516241748f},{0.9996760121f,-0.0254533053f},{-0.0624838363f,-0.9980459760f},
	{0.7120139305f,-0.7021653386f},{0.8917660409f,-0.4524967717f},{0.1094842955f,-0.9939885256f},{-0.8730880804f,-0.4875625128f},{0.2594811489f,-0.9657481729f},{-0.6690063346f,-0.7432567015f},{-0.9996834972f,0.0251576121f},{-0.8803608671f,0.4743044842f},{-0.8166554937f,0.5771254669f},{0.8955599676f,0.4449408324f},{-0.9398321388f,0.3416365773f},{0.0761545140f,0.9970960285f},{-0.7147270565f,0.6994034849f},{0.8707354457f,0.4917517499f},{-0.9580008579f,0.2867653330f},{0.4905965632f,0.8713868327f},
	{0.7867759440f,0.6172387009f},{0.1079711577f,0.9941540269f},{0.2686638979f,0.9632339851f},{0.6113487322f,-0.7913613129f},{-0.5307705840f,0.8475155380f},{-0.7837268286f,0.6211056739f},{-0.8558691039f,0.5171924952f},{-0.5726093896f,-0.8198283277f},{-0.9830740914f,-0.1832084353f},{0.7087766359f,0.7054329737f},{0.6807027153f,0.7325597678f},{-0.0886470879f,0.9960630973f},{0.6704485923f,0.7419559859f},{-0.1350735482f,0.9908355749f},{-0.9381333003f,-0.3462743290f},{0.9756655376f,0.2192641299f},
	{0.4231433671f,-0.9060627411f},{-0.4959787385f,-0.8683346653f},{0.1005554325f,0.9949314574f},{-0.7645857281f,-0.6445220433f},{-0.5859053796f,-0.8103794704f},{-0.9751154306f,-0.2216977607f},{-0.6972258572f,0.7168515217f},{0.7907012002f,0.6122022640f},{-0.9109899213f,-0.4124286160f},{-0.9584307894f,0.2853251160f},{-0.8269529333f,0.5622711500f},{0.2608264719f,-0.9653857009f},{-0.7773760119f,-0.6290361962f},{0.7606456974f,0.6491672535f},{-0.8961083758f,0.4438353060f},{-0.9838134719f,-0.1791955706f},
	{0.7338893576f,-0.6792690269f},{0.2161226729f,-0.9763662173f},{0.6735098910f,0.7391782104f},{-0.5512056873f,0.8343693968f},{0.6899744332f,0.7238337389f},{0.8680048310f,0.4965557504f},{0.5897430311f,0.8075909592f},{-0.8950444221f,-0.4459769977f},{-0.3595752773f,-0.9331160806f},{0.8209486981f,-0.5710019572f},{-0.2912360132f,0.9566512346f},{-0.9965011374f,-0.0835792032f},{0.9766994634f,0.2146116448f},{0.7387908220f,-0.6739348049f},{-0.4730947722f,0.8810115417f},{0.8946479441f,0.4467718167f},
	{-0.6943628971f,-0.7196250184f},{-0.6620468182f,-0.7494624810f},{-0.0887255502f,0.9960561112f},{-0.7512250855f,0.6600461127f},{-0.5322986898f,-0.8465566164f},{0.5226295385f,-0.8525598897f},{0.2296318375f,-0.9732775654f},{0.7915307344f,0.6111293616f},{-0.2756485999f,-0.9612584717f},{-0.6900234522f,-0.7237870097f},{0.0709058809f,-0.9974830104f},{0.5981278485f,-0.8014006968f},{0.3033429312f,0.9528814544f},{-0.7253142797f,-0.6884178931f},{-0.9855874307f,-0.1691668301f},{-0.1761843396f,0.9843571905f},
	{-0.6438468325f,0.7651544003f},{-0.9956136595f,-0.0935598261f},{0.8541580762f,-0.5200134429f},{-0.9999807666f,-0.0062021258f},{-0.0215241625f,-0.9997683284f},{-0.8705983095f,0.4919944954f},{-0.1197138014f,-0.9928084436f},{-0.9921077810f,-0.1253880012f},{-0.9091181546f,-0.4165383308f},{0.7886105360f,-0.6148930171f},{-0.9946364020f,-0.1034332049f},{0.4211256853f,-0.9070022917f},{0.3110430857f,-0.9503958117f},{-0.4031127839f,0.9151503065f},{0.7610684239f,-0.6486716073f},{0.7685674467f,0.6397687707f},
	{0.1522715550f,-0.9883386937f},{-0.9364648723f,0.3507613761f},{0.1681333739f,0.9857642561f},{-0.3567427907f,-0.9342026446f},{-0.4184454830f,-0.9082419159f},{-0.9877477800f,0.1560587169f},{0.8705250765f,0.4921240607f},{-0.8911701067f,-0.4536693080f},{-0.7315350966f,0.6818037859f},{0.6030885658f,0.7976742329f},{-0.4149130821f,0.9098610522f},{0.7585339481f,0.6516335240f},{0.6963196535f,0.7177318024f},{0.8332685012f,-0.5528685241f},{-0.8086815232f,0.5882467118f},{0.7518116724f,0.6593778956f},
	{-0.3490535894f,0.9371027648f},{0.6972110903f,-0.7168658839f},{-0.8795676928f,-0.4757737632f},{-0.6442331882f,0.7648291307f},{0.6610236811f,0.7503650398f},{-0.9853565782f,0.1705063456f},{-0.5903384580f,-0.8071558121f},{0.0984360212f,-0.9951433815f},{0.5646534882f,-0.8253280792f},{-0.6023259233f,-0.7982502628f},{-0.3539248861f,0.9352738503f},{0.5132728656f,0.8582254747f},{0.9380385118f,-0.3465310238f},{-0.7599270056f,0.6500084200f},{-0.7425936564f,-0.6697422351f},{-0.6679610562f,0.7441962291f},
	{-0.3018497816f,-0.9533555000f},{0.8144782660f,0.5801940659f},{0.0377743027f,-0.9992862963f},{-0.7514235086f,-0.6598202110f},{0.9662556939f,0.2575848092f},{-0.4720194901f,0.8815881130f},{-0.4350541260f,-0.9004043022f},{0.7091901235f,-0.7050172826f},{0.9293792090f,0.3691263820f},{0.9997434357f,-0.0226508884f},{0.8306320299f,0.5568217228f},{-0.9434019629f,-0.3316515286f},{-0.1331337590f,0.9910980790f},{0.5048413216f,-0.8632121640f},{0.3711995273f,-0.9285531277f},{0.9855209100f,0.1695539323f},
	{0.7401857005f,-0.6724025050f},{-0.9999981398f,-0.0019288419f},{-0.2144033253f,0.9767452145f},{0.4808624681f,-0.8767960349f},{-0.4138358850f,0.9103515037f},{0.6442293050f,-0.7648324016f},{0.9626648696f,0.2706960452f},{0.1833665934f,-0.9830446035f},{0.5794129000f,0.8150341657f},{0.0140444687f,-0.9999013716f},{0.4388494993f,-0.8985605806f},{0.5213612322f,0.8533360801f},{-0.5281609948f,0.8491442537f},{-0.9745306846f,-0.2242541966f},{-0.9904373013f,-0.1379635899f},{0.9100232252f,-0.4145572694f},
	{-0.9914057719f,0.1308227633f},{0.7892627765f,0.6140555916f},{0.3364421659f,0.9417041303f},{-0.9416099764f,-0.3367055870f},{0.7802732656f,-0.6254387508f},{0.8863028710f,0.4631060578f},{0.6524471291f,-0.7578342456f},{0.5762186726f,-0.8172955655f},{-0.0898764466f,-0.9959529228f},{-0.2177026782f,-0.9760151351f},{-0.9720345052f,0.2348380732f},{-0.0572253886f,-0.9983612848f},{0.8105983127f,0.5856025746f},{0.3410261032f,-0.9400538266f},{0.6452309645f,-0.7639875669f},{-0.7810612152f,0.6244544645f},
	{0.9989395718f,0.0460405457f},{-0.8082478150f,0.5888424828f},{0.6370177929f,0.7708490978f},{0.5844658772f,-0.8114182882f},{0.2054070861f,0.9786766212f},{0.0559605220f,-0.9984329822f},{-0.9958275610f,0.0912549658f},{0.8934091650f,-0.4492438803f},{-0.9315168240f,-0.3636982357f},{0.3289694690f,0.9443405575f},{-0.3193837488f,-0.9476254645f},{0.7314755657f,-0.6818676535f},{-0.7913517714f,-0.6113610831f},{-0.2204109786f,0.9754070948f},{0.9955900414f,-0.0938108173f},{-0.7112353139f,-0.7029540015f},
	{-0.7935008741f,-0.6085691109f},{-0.9961918204f,-0.0871886288f},{-0.9714163995f,-0.2373819260f},{-0.9566188669f,0.2913423132f},{0.2748495632f,0.9614872426f},{-0.4681743221f,0.8836361266f},{-0.9614449642f,-0.2749974196f},{0.5851940720f,-0.8108932717f},{0.4532946061f,-0.8913607575f},{-0.9916113176f,0.1292555410f},{0.9424795870f,-0.3342637104f},{-0.9813704753f,-0.1921249337f},{-0.6538429571f,-0.7566302845f},{0.2923335053f,-0.9563164339f},{-0.2246660704f,-0.9744358146f},{-0.1800781949f,0.9836522982f},
	{-0.9581216256f,-0.2863615732f},{0.5522150820f,0.8337016872f},{-0.9296791922f,0.3683701937f},{0.6431836990f,0.7657119102f},{0.9997325981f,-0.0231242777f},{-0.4606920354f,0.8875600535f},{-0.2148721265f,0.9766421910f},{0.3482070809f,0.9374176384f},{0.3075517813f,0.9515313457f},{0.6274756393f,-0.7786361937f},{0.8910881765f,-0.4538302125f},{-0.6397771309f,-0.7685604874f},{-0.4479080125f,-0.8940796454f},{-0.5247665011f,-0.8512462154f},{-0.8386507094f,0.5446696133f},{0.3901291416f,0.9207601495f},
	{0.1458336921f,-0.9893091197f},{0.0162461315f,-0.9998680229f},{-0.8273199879f,0.5617309299f},{0.5611100679f,-0.8277411985f},{-0.8380219841f,0.5456364670f},{-0.9856122234f,0.1690223212f},{-0.8613986180f,-0.5079295433f},{0.6398413916f,0.7685069899f},{0.2694510795f,-0.9630140787f},{0.4327334514f,0.9015219132f},{-0.9960265354f,0.0890569528f},{-0.9395706550f,-0.3423550559f},{-0.8846996446f,-0.4661614943f},{0.7642113189f,-0.6449659371f},{-0.7002080528f,0.7139388509f},{0.6645082560f,0.7472809229f},
};

const FVector GCell3D[] =
{
	{0.3752498686f,-0.6760585049f,-0.6341391283f},{0.6871880960f,-0.0913617650f,-0.7207118346f},{0.2248135212f,0.1681325679f,0.9597866014f},{0.6692006647f,-0.6688468686f,0.3237504235f},{-0.4376476931f,-0.4822753902f,-0.7588642466f},{0.6139972552f,-0.7891068824f,-0.0178241048f},{0.9494563929f,-0.1877509944f,0.2515593809f},{0.8065108882f,0.5484709140f,0.2207257205f},{-0.2218812853f,-0.4633394430f,-0.8579541106f},{0.8484661167f,-0.4050542082f,0.3406410681f},{0.5551817596f,0.3218158513f,0.7669470462f},{0.2133903499f,0.2546493823f,-0.9431957648f},{0.5195126593f,-0.3753271935f,0.7676171537f},{-0.6440141975f,0.4745384887f,-0.6000491115f},{-0.5192897331f,0.4812546520f,-0.7062096948f},{-0.3697654077f,-0.8934416489f,0.2550207115f},
	{-0.0792777965f,-0.6737085076f,0.7347325213f},{0.4187757321f,0.7469917228f,0.5163625202f},{-0.7500787310f,0.3826230411f,-0.5394270162f},{0.6579554632f,0.6751013678f,0.3336656285f},{-0.6859803838f,-0.7248119515f,-0.0638635111f},{-0.6878407087f,-0.3224276742f,-0.6503195787f},{0.9490848347f,-0.0207619094f,0.3143356798f},{0.5795829433f,-0.6404268166f,-0.5039217245f},{-0.5325976529f,-0.5292028444f,0.6605180464f},{-0.1363699466f,0.7151414636f,-0.6855479011f},{0.4176658790f,-0.6144655059f,-0.6693185756f},{-0.9108236468f,-0.3699121240f,0.1832083647f},{0.4438605427f,0.6942067212f,-0.5666258437f},{0.8192948870f,-0.4481558248f,0.3576482138f},{-0.4033873915f,-0.6366894559f,-0.6571949095f},{-0.2817317705f,0.5956568471f,-0.7522101635f},
	{0.3969665622f,0.5642745390f,-0.7238865886f},{0.5323450134f,0.7145584688f,0.4538887323f},{-0.6833017297f,0.6871918316f,0.2467106257f},{0.3881436661f,0.5657918509f,0.7274778869f},{-0.7119144767f,-0.6275978114f,0.3151170655f},{-0.2306979838f,0.4146983062f,-0.8802293764f},{-0.9398873022f,0.2638993789f,-0.2167232729f},{0.1701906676f,-0.7926331380f,0.5854637865f},{-0.4261839496f,0.5706133514f,0.7019741052f},{-0.0037122955f,0.8606546462f,0.5091756071f},{-0.7346750040f,0.6490900316f,0.1973189533f},{-0.3195046015f,-0.8242699196f,0.4674354600f},{0.7345307424f,0.6765819124f,0.0519759960f},{0.9766246496f,0.1959534069f,0.0883547180f},{-0.0200373518f,-0.8426769757f,0.5380464843f},{-0.4824156342f,-0.5917672797f,-0.6458224544f},
	{0.4245892007f,0.7517364266f,-0.5045952393f},{0.9072427669f,0.0325255923f,0.4193478840f},{0.5933468080f,0.0883617105f,0.8000823542f},{-0.8911762541f,0.4475064813f,-0.0744502066f},{-0.7657571834f,-0.1418643552f,-0.6272881641f},{-0.5268198896f,0.7343428473f,-0.4280203110f},{-0.8801903279f,0.3870192548f,-0.2747382083f},{-0.6296409617f,-0.7716703522f,-0.0898728373f},{-0.0949248134f,0.4839898327f,0.8699098354f},{-0.4920470525f,0.7437439055f,0.4524761885f},{0.7307666154f,-0.5989573348f,-0.3274603257f},{-0.2514540636f,-0.8357068955f,0.4882262167f},{-0.3356210347f,0.6086049038f,-0.7189983256f},{-0.3522787894f,0.9194627258f,0.1746079907f},{0.8784788500f,0.4718297238f,0.0751772698f},{-0.7424096346f,-0.2650335884f,-0.6152927202f},
	{0.5757585274f,-0.6470352599f,0.4998474673f},{0.4519299338f,-0.5555181303f,-0.6979677227f},{0.6420368628f,0.1222351235f,0.7568667263f},{-0.1128478447f,0.7802044684f,-0.6152612058f},{0.4998748830f,-0.8636947022f,0.0644714099f},{0.5291681739f,-0.2341352163f,-0.8155744872f},{-0.5098837195f,0.6830308740f,-0.5229602449f},{0.5639583502f,-0.5005858287f,0.6567836838f},{-0.8456386526f,0.2334616211f,-0.4799905631f},{-0.9657134875f,0.2576877608f,0.0315353459f},{-0.5764373420f,0.6666816727f,0.4724992466f},{-0.5666013014f,-0.7663996863f,-0.3026458097f},{0.5667702405f,0.7942019820f,-0.2191225827f},{-0.4813165820f,0.6189308788f,-0.6206922870f},{0.7313389916f,0.6071033261f,0.3107552588f},{-0.3805628566f,-0.4206058253f,0.8235670294f},
	{-0.6512675909f,-0.3957336915f,0.6474915988f},{-0.2787156951f,-0.8170257484f,-0.5047637941f},{0.8648059114f,-0.1043240417f,0.4911488878f},{-0.9730216276f,0.0002167596f,-0.2307138167f},{-0.8335820906f,0.1816339018f,-0.5216800015f},{0.2673159641f,-0.6838094939f,0.6789305939f},{0.2311501480f,-0.2495341969f,0.9403734863f},{0.0128621464f,-0.7116756954f,0.7023903970f},{0.6774953261f,-0.0336167362f,0.7347584625f},{0.6542885718f,-0.3350836431f,0.6779567958f},{-0.0254545016f,0.2137186039f,0.9765635805f},{0.2101238586f,0.2557996786f,-0.9436177661f},{-0.5572105885f,0.7490117093f,-0.3584659250f},{0.8137056720f,0.4942936549f,-0.3058706624f},{-0.7546026951f,-0.3526868530f,0.5533414464f},{-0.2502500006f,-0.3952445435f,-0.8838306897f},
	{-0.9979289381f,-0.0459964767f,0.0449684181f},{0.7024037039f,-0.7115787471f,0.0168737496f},{0.0899087462f,0.0802289976f,-0.9927133148f},{0.8170812432f,0.5362268157f,-0.2117523180f},{0.4226980265f,-0.8258613686f,0.3732015249f},{-0.2442153475f,0.1114171723f,0.9632990593f},{-0.9183326731f,0.3882823051f,-0.0768241700f},{0.6068222411f,-0.7915404457f,-0.0723221305f},{0.8186766910f,0.3250957662f,0.4733721775f},{-0.7236735282f,0.6401346464f,0.2579229713f},{-0.5383903295f,-0.2662724517f,0.7995216286f},{-0.6269337242f,-0.6727907114f,0.3928189967f},{-0.0939331121f,-0.9947308180f,0.0410751767f},{0.9203878539f,-0.3596358977f,0.1534542912f},{-0.7256396824f,0.2344610069f,0.6468965045f},{0.6292431149f,-0.6645215546f,0.4030684878f},
	{0.4234156978f,-0.7107590611f,-0.5617300988f},{0.0066856880f,-0.4646617327f,-0.8854630290f},{-0.2598694113f,0.6717191355f,0.6937299850f},{0.6408036421f,0.5101893498f,-0.5736527866f},{0.0589987162f,0.1185768238f,-0.9911905409f},{0.7090281418f,0.2360050930f,-0.6645153800f},{-0.5905222072f,-0.7811024061f,0.2028855685f},{0.3128214264f,0.5089325193f,0.8019541421f},{-0.6919258260f,0.6073187658f,-0.3903877149f},{0.3634019349f,-0.7930732557f,-0.4888495114f},{-0.6772511147f,-0.6822767155f,-0.2753714057f},{-0.3204583896f,0.3201532885f,-0.8915202143f},{-0.3906740409f,0.7545302807f,0.5273119089f},{-0.3342190395f,0.1072664448f,0.9363714773f},{-0.5177795920f,0.6784033173f,-0.5212228249f},{-0.6817711267f,-0.6595924967f,-0.3164267200f},
	{0.6422383105f,0.7276509498f,0.2409440761f},{0.4388482478f,0.5586689436f,-0.7037764040f},{0.2968562611f,-0.6498636788f,-0.6996810411f},{-0.2019778353f,0.6789333174f,-0.7058714505f},{0.6014865048f,0.7105966551f,-0.3650566783f},{0.9519280722f,-0.2872214155f,0.1064744278f},{0.3398889569f,0.4967462170f,0.7985729102f},{0.8179709354f,-0.3880337977f,0.4246802570f},{0.2365522154f,0.7324070604f,-0.6384535592f},{0.3262175096f,-0.9326634749f,0.1540161646f},{-0.8060715954f,-0.5867839255f,-0.0770273194f},{-0.2068642503f,0.8003043651f,-0.5627789132f},{0.6208057279f,-0.1631882481f,-0.7667919169f},{-0.5274282502f,-0.6796374681f,-0.5098159990f},{-0.3722334928f,-0.8066678503f,0.4590525092f},{-0.8923412971f,0.4238177418f,0.1552595611f},
	{0.5341834201f,0.7715863549f,0.3454020420f},{-0.3663701513f,0.5455367347f,0.7537656024f},{-0.6114600319f,-0.0320511540f,0.7906259247f},{0.5026307556f,-0.6005545066f,-0.6218493452f},{0.8396151729f,-0.5423640002f,0.0297935007f},{0.9245042467f,0.3569205906f,-0.1337893489f},{-0.7994843957f,-0.5820717520f,-0.1483818606f},{-0.5357200589f,0.6407354361f,0.5499655620f},{-0.6283359739f,0.7777142984f,0.0188248241f},{-0.6135188600f,-0.0995642862f,-0.7833783002f},{-0.8756320080f,0.1100002681f,0.4702855809f},{-0.5278879423f,0.8136349123f,0.2435827372f},{0.9087491985f,0.2923431904f,0.2978428332f},{-0.0350021547f,0.9735794425f,0.2256499906f},{-0.2613657980f,0.8324974864f,0.4885036897f},{-0.5795235410f,-0.6179617717f,0.5312962584f},
	{-0.3765052689f,-0.9248386523f,0.0540115699f},{-0.7439825200f,-0.6448780771f,0.1749922158f},{0.4257318052f,-0.5274402761f,-0.7352273018f},{-0.1214508921f,-0.7862170565f,0.6058980284f},{0.8561809753f,0.2682099744f,0.4416079111f},{0.6802835104f,-0.5848777694f,0.4417378638f},{-0.5452131039f,-0.6364561467f,0.5455879807f},{-0.1997156478f,-0.7167402514f,-0.6681295324f},{0.4562348357f,-0.8677012494f,0.1973431441f},{-0.8117043010f,0.4205286707f,0.4053292055f},{0.6779396200f,-0.7007832749f,0.2220375492f},{-0.9237819106f,0.2432724510f,0.2957118467f},{0.6973511259f,-0.1899846085f,0.6910913512f},{-0.5189506000f,-0.6146124977f,0.5940890106f},{0.5517320032f,-0.8093357692f,-0.2014135283f},{-0.3967108310f,-0.0354509699f,-0.9172588213f},
	{0.5493762815f,-0.7191590868f,-0.4254361401f},{-0.2507853002f,0.7478645848f,-0.6146586825f},{0.4788634005f,0.3623517328f,-0.7996193253f},{0.3873335160f,0.8436992512f,-0.3716777111f},{-0.2176515694f,-0.2445711729f,-0.9448876842f},{0.6749832419f,0.6897356637f,-0.2620349924f},{0.2148283022f,-0.1708070787f,0.9615995749f},{-0.7521815872f,0.4639272368f,-0.4679683524f},{0.4697000159f,-0.7917186656f,0.3905937144f},{0.7890593699f,0.0298002543f,0.6135937220f},{-0.7606162952f,0.6334156172f,0.1422937358f},{0.0108339784f,-0.9815544807f,0.1908754211f},{0.5254091908f,-0.2307217304f,0.8189704912f},{-0.6748025877f,0.1080823318f,-0.7300408736f},{0.7510915240f,0.5167601798f,-0.4108776451f},{0.0525905614f,-0.8451200160f,-0.5319834504f},
	{0.0188948123f,0.4415725620f,-0.8970265651f},{-0.6037423727f,0.5876789172f,-0.5386359045f},{-0.6542965129f,-0.6365908737f,0.4082255906f},{0.0887330108f,0.6835016600f,0.7245356676f},{-0.6191345671f,0.5849723959f,0.5239080873f},{0.4331858488f,0.1164114357f,-0.8937552226f},{-0.3858351946f,-0.7379813884f,-0.5536376730f},{-0.1429059747f,-0.9613237178f,0.2354455182f},{0.4118221036f,-0.9071943084f,-0.0860293075f},{-0.6247153214f,-0.7682111105f,-0.1399373318f},{-0.6114230140f,0.6390744590f,-0.4666323327f},{0.5542939606f,-0.6193582980f,0.5560157407f},{-0.9432768808f,0.2807257131f,0.1772619533f},{-0.4567870451f,-0.0180086879f,-0.8893937725f},{-0.7349133547f,0.3776607289f,-0.5632714576f},{0.3993044890f,0.7207567823f,-0.5666264959f},
	{-0.7474927672f,0.5536661486f,-0.3670263736f},{0.0258941975f,-0.9974053117f,-0.0671724258f},{0.7839158210f,-0.0204720001f,0.6205295181f},{0.6138668752f,-0.6739453804f,-0.4110536264f},{0.4276376047f,-0.5607471297f,0.7090054553f},{-0.4347886353f,0.8815553192f,0.1838995970f},{0.0294784130f,0.8275977415f,-0.5605470555f},{-0.8337427460f,0.3928902456f,0.3879565548f},{0.3817221742f,0.5509913960f,0.7420893903f},{-0.8743368359f,0.4247623676f,-0.2347595118f},{-0.3823443796f,-0.3436948871f,-0.8577217497f},{-0.6829243811f,-0.3653537677f,0.6325590203f},{-0.3681903049f,0.3181702902f,-0.8736152276f},{-0.3676268330f,-0.6067173171f,0.7048011129f},{-0.4345833730f,-0.8984128477f,-0.0631794827f},{0.2358919950f,0.4220839766f,0.8753285574f},
	{-0.6874880269f,0.7238407199f,-0.0584365047f},{-0.5115661773f,-0.7766913695f,-0.3674922622f},{-0.5534962601f,0.6460037842f,-0.5256624401f},{0.5632777056f,0.2544775664f,0.7861039337f},{0.6861915320f,0.6488840578f,0.3287714416f},{-0.0509587159f,0.8050168330f,0.5910593099f},{-0.0686578506f,-0.9183807036f,-0.3896960134f},{-0.5975288531f,0.4144046357f,0.6864605361f},{-0.6429790056f,0.2705872080f,0.7164918431f},{-0.3729361548f,-0.8813684494f,-0.2900142770f},{0.2237917666f,0.6985971877f,-0.6796169617f},{0.6046773225f,-0.7795603017f,0.1632515592f},{-0.5041542295f,-0.8624480731f,0.0448534749f},{-0.0397219117f,0.5532697017f,0.8320545697f},{0.7028828406f,0.7111795210f,0.0133940806f},{-0.5560856498f,-0.7798160574f,-0.2874989857f},
	{0.5898328456f,0.5225859041f,0.6156307230f},{-0.9308076766f,0.1261859368f,0.3430367014f},{0.4617069864f,0.3398033582f,0.8193658136f},{0.3190983137f,-0.7472173667f,-0.5829600957f},{0.9116567753f,-0.4032647119f,0.0791169778f},{-0.4502955400f,-0.4246578154f,0.7854296063f},{0.3346334459f,0.8481212377f,-0.4107442306f},{0.8525005645f,-0.2144838537f,0.4766964066f},{0.2528483381f,0.3431714491f,-0.9045999527f},{-0.8306630147f,0.5310188231f,-0.1673856787f},{-0.6880390622f,0.6682978632f,0.2828077348f},{0.7448684026f,0.3110433206f,-0.5902737632f},{-0.1963355843f,0.9263293599f,-0.3215062290f},{-0.5900257974f,-0.6155600569f,-0.5224513133f},{0.9097057294f,0.0716978440f,-0.4090169985f},{-0.2509196808f,0.8985888773f,-0.3599685311f},
};


static float InterpHermiteFunc(float T) { return T * T * (3 - 2 * T); }
static float InterpQuinticFunc(float T) { return T * T * T * (T * (T * 6 - 15) + 10); }
static float CubicLerp(float A, float B, float C, float D, float T)
{
	float P = (D - C) - (A - B);
	return T * T * T * P + T * T * ((A - B) - P) + T * (C - A) + B;
}

const float CUBIC_3D_BOUNDING = 1 / (float(1.5) * float(1.5) * float(1.5));
const float CUBIC_2D_BOUNDING = 1 / (float(1.5) * float(1.5));

static const float G4 = (5 - sqrt(float(5))) / 20;
static const float F4 = (sqrt(float(5)) - 1) / 4;

static const float F3 = 1 / float(3);
static const float G3 = 1 / float(6);

static const float SQRT3 = float(1.7320508075688772935274463415059);
static const float F2 = float(0.5) * (SQRT3 - float(1.0));
static const float G2 = (float(3.0) - SQRT3) / float(6.0);

// Hashing
#define X_PRIME 1619
#define Y_PRIME 31337
#define Z_PRIME 6971
#define W_PRIME 1013

// public 2D
float UFastNoiseFunctionLibrary::GetValue2D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y)
{
	return SingleValue2D(Seed, Interpolation, X * Frequency, Y * Frequency);
}

float UFastNoiseFunctionLibrary::GetValueFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y)
{
	X *= Frequency;
	Y *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleValueFractalFbm2D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y);
	case EFractalType::Billow:
		return SingleValueFractalBillow2D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y);
	case EFractalType::RigidMulti:
		return SingleValueFractalRigidMulti2D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y);
	default:
		return 0;
	}
}

float UFastNoiseFunctionLibrary::GetPerlin2D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y)
{
	return SinglePerlin2D(Seed, Interpolation, X * Frequency, Y * Frequency);
}

float UFastNoiseFunctionLibrary::GetPerlinFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y)
{
	X *= Frequency;
	Y *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SinglePerlinFractalFbm2D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y);
	case EFractalType::Billow:
		return SinglePerlinFractalBillow2D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y);
	case EFractalType::RigidMulti:
		return SinglePerlinFractalRigidMulti2D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y);
	default:
		return 0;
	}
}

float UFastNoiseFunctionLibrary::GetSimplex2D(int32 Seed, float Frequency, float X, float Y)
{
	return SingleSimplex2D(Seed, X * Frequency, Y * Frequency);
}

float UFastNoiseFunctionLibrary::GetSimplexFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y)
{
	X *= Frequency;
	Y *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleSimplexFractalFbm2D(Seed, Lacunarity, Gain, Octaves, X, Y);
	case EFractalType::Billow:
		return SingleSimplexFractalBillow2D(Seed, Lacunarity, Gain, Octaves, X, Y);
	case EFractalType::RigidMulti:
		return SingleSimplexFractalRigidMulti2D(Seed, Lacunarity, Gain, Octaves, X, Y);
	default:
		return 0;
	}
}

float UFastNoiseFunctionLibrary::GetWhiteNoise2D(int32 Seed, float X, float Y)
{
	return SeededCoordinateValue2D(Seed,
		*reinterpret_cast<int32*>(&X) ^ (*reinterpret_cast<int32*>(&X) >> 16),
		*reinterpret_cast<int32*>(&Y) ^ (*reinterpret_cast<int32*>(&Y) >> 16));
}

float UFastNoiseFunctionLibrary::GetWhiteNoiseInt2D(int32 Seed, int32 X, int32 Y)
{
	return SeededCoordinateValue2D(Seed, X, Y);
}

float UFastNoiseFunctionLibrary::GetCubic2D(int32 Seed, float Frequency, float X, float Y)
{
	X *= Frequency;
	Y *= Frequency;

	return SingleCubic2D(Seed, X, Y);
}

float UFastNoiseFunctionLibrary::GetCubicFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y)
{
	X *= Frequency;
	Y *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleCubicFractalFbm2D(Seed, Lacunarity, Gain, Octaves, X, Y);
	case EFractalType::Billow:
		return SingleCubicFractalBillow2D(Seed, Lacunarity, Gain, Octaves, X, Y);
	case EFractalType::RigidMulti:
		return SingleCubicFractalRigidMulti2D(Seed, Lacunarity, Gain, Octaves, X, Y);
	default:
		return 0;
	}
}

void UFastNoiseFunctionLibrary::GradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y)
{
	SingleGradientPerturb2D(Seed, Perturb, Frequency, Interpolation, X, Y);
}

void UFastNoiseFunctionLibrary::GradientPerturbFractal2D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float& X, float& Y)
{
	float amp = Perturb * CalculateFractalBounding(Octaves, Gain);;
	float freq = Frequency;
	int32 i = 0;

	SingleGradientPerturb2D(Seed, amp, Frequency, Interpolation, X, Y);

	while (++i < Octaves)
	{
		freq *= Lacunarity;
		amp *= Gain;
		SingleGradientPerturb2D(Seed, amp, freq, Interpolation, X, Y);
	}
}

// public 3D
float UFastNoiseFunctionLibrary::GetValue3D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y, float Z)
{
	return SingleValue3D(Seed, Interpolation, X * Frequency, Y * Frequency, Z * Frequency);
}

float UFastNoiseFunctionLibrary::GetValueFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y, float Z)
{
	X *= Frequency;
	Y *= Frequency;
	Z *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleValueFractalFbm3D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y, Z);
	case EFractalType::Billow:
		return SingleValueFractalBillow3D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y, Z);
	case EFractalType::RigidMulti:
		return SingleValueFractalRigidMulti3D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y, Z);
	default:
		return 0;
	}
}

float UFastNoiseFunctionLibrary::GetPerlin3D(int32 Seed, float Frequency, EInterpolation Interpolation, float X, float Y, float Z)
{
	return SinglePerlin3D(Seed, Interpolation, X * Frequency, Y * Frequency, Z * Frequency);
}

float UFastNoiseFunctionLibrary::GetPerlinFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, float X, float Y, float Z)
{
	X *= Frequency;
	Y *= Frequency;
	Z *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SinglePerlinFractalFbm3D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y, Z);
	case EFractalType::Billow:
		return SinglePerlinFractalBillow3D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y, Z);
	case EFractalType::RigidMulti:
		return SinglePerlinFractalRigidMulti3D(Seed, Lacunarity, Gain, Octaves, Interpolation, X, Y, Z);
	default:
		return 0;
	}
}

float UFastNoiseFunctionLibrary::GetSimplex3D(int32 Seed, float Frequency, float X, float Y, float Z)
{
	return SingleSimplex3D(Seed, X * Frequency, Y * Frequency, Z * Frequency);
}

float UFastNoiseFunctionLibrary::GetSimplexFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y, float Z)
{
	X *= Frequency;
	Y *= Frequency;
	Z *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleSimplexFractalFbm3D(Seed, Lacunarity, Gain, Octaves, X, Y, Z);
	case EFractalType::Billow:
		return SingleSimplexFractalBillow3D(Seed, Lacunarity, Gain, Octaves, X, Y, Z);
	case EFractalType::RigidMulti:
		return SingleSimplexFractalRigidMulti3D(Seed, Lacunarity, Gain, Octaves, X, Y, Z);
	default:
		return 0;
	}
}

float UFastNoiseFunctionLibrary::GetWhiteNoise3D(int32 Seed, float X, float Y, float Z)
{
	return SeededCoordinateValue3D(Seed,
		*reinterpret_cast<int32*>(&X) ^ (*reinterpret_cast<int32*>(&X) >> 16),
		*reinterpret_cast<int32*>(&Y) ^ (*reinterpret_cast<int32*>(&Y) >> 16),
		*reinterpret_cast<int32*>(&Z) ^ (*reinterpret_cast<int32*>(&Z) >> 16));
}

float UFastNoiseFunctionLibrary::GetWhiteNoiseInt3D(int32 Seed, int32 X, int32 Y, int32 Z)
{
	return SeededCoordinateValue3D(Seed, X, Y, Z);
}

float UFastNoiseFunctionLibrary::GetCubic3D(int32 Seed, float Frequency, float X, float Y, float Z)
{
	return SingleCubic3D(Seed, X * Frequency, Y * Frequency, Z * Frequency);
}

float UFastNoiseFunctionLibrary::GetCubicFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y, float Z)
{
	X *= Frequency;
	Y *= Frequency;
	Z *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleCubicFractalFbm3D(Seed, Lacunarity, Gain, Octaves, X, Y, Z);
	case EFractalType::Billow:
		return SingleCubicFractalBillow3D(Seed, Lacunarity, Gain, Octaves, X, Y, Z);
	case EFractalType::RigidMulti:
		return SingleCubicFractalRigidMulti3D(Seed, Lacunarity, Gain, Octaves, X, Y, Z);
	default:
		return 0;
	}
}

void UFastNoiseFunctionLibrary::GradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y, float& Z)
{
	SingleGradientPerturb3D(Seed, Perturb, Frequency, Interpolation, X, Y, Z);
}

void UFastNoiseFunctionLibrary::GradientPerturbFractal3D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float& X, float& Y, float& Z)
{
	float amp = Perturb * CalculateFractalBounding(Octaves, Gain);;
	float freq = Frequency;
	int32 i = 0;

	SingleGradientPerturb3D(Seed, amp, Frequency, Interpolation, X, Y, Z);

	while (++i < Octaves)
	{
		freq *= Lacunarity;
		amp *= Gain;
		SingleGradientPerturb3D(Seed, amp, freq, Interpolation, X, Y, Z);
	}
}

// public 4D
float UFastNoiseFunctionLibrary::GetSimplex4D(int32 Seed, float Frequency, float X, float Y, float Z, float W)
{
	return SingleSimplex4D(Seed, X * Frequency, Y * Frequency, Z * Frequency, W * Frequency);
}

float UFastNoiseFunctionLibrary::GetSimplexFractal4D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, float X, float Y, float Z, float W)
{
	X *= Frequency;
	Y *= Frequency;
	Z *= Frequency;
	W *= Frequency;

	switch (FractalType)
	{
	case EFractalType::FBM:
		return SingleSimplexFractalFbm4D(Seed, Lacunarity, Gain, Octaves, X, Y, Z, W);
	case EFractalType::Billow:
		return SingleSimplexFractalBillow4D(Seed, Lacunarity, Gain, Octaves, X, Y, Z, W);
	case EFractalType::RigidMulti:
		return SingleSimplexFractalRigidMulti4D(Seed, Lacunarity, Gain, Octaves, X, Y, Z, W);
	default:
		return 0;
	}
}

float UFastNoiseFunctionLibrary::GetWhiteNoise4D(int32 Seed, float X, float Y, float Z, float W)
{
	return SeededCoordinateValue4D(Seed,
		*reinterpret_cast<int32*>(&X) ^ (*reinterpret_cast<int32*>(&X) >> 16),
		*reinterpret_cast<int32*>(&Y) ^ (*reinterpret_cast<int32*>(&Y) >> 16),
		*reinterpret_cast<int32*>(&Z) ^ (*reinterpret_cast<int32*>(&Z) >> 16),
		*reinterpret_cast<int32*>(&W) ^ (*reinterpret_cast<int32*>(&W) >> 16));
}

float UFastNoiseFunctionLibrary::GetWhiteNoiseInt4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W)
{
	return SeededCoordinateValue4D(Seed, X, Y, Z, W);
}

float UFastNoiseFunctionLibrary::GetValue2D(int32 Seed, float Frequency, EInterpolation Interpolation, FVector2D Coordinates)
{
	return GetValue2D(Seed, Frequency, Interpolation, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetValueFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, FVector2D Coordinates)
{
	return GetValueFractal2D(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetPerlin2D(int32 Seed, float Frequency, EInterpolation Interpolation, FVector2D Coordinates)
{
	return GetPerlin2D(Seed, Frequency, Interpolation, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetPerlinFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, FVector2D Coordinates)
{
	return GetPerlinFractal2D(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetSimplex2D(int32 Seed, float Frequency, FVector2D Coordinates)
{
	return GetSimplex2D(Seed, Frequency, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetSimplexFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, FVector2D Coordinates)
{
	return GetSimplexFractal2D(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetWhiteNoise2D(int32 Seed, FVector2D Coordinates)
{
	return GetWhiteNoise2D(Seed, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetWhiteNoiseInt2D(int32 Seed, FIntPoint Coordinates)
{
	return GetWhiteNoiseInt2D(Seed, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetCubic2D(int32 Seed, float Frequency, FVector2D Coordinates)
{
	return GetCubic2D(Seed, Frequency, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetCubicFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, FVector2D Coordinates)
{
	return GetCubicFractal2D(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates.X, Coordinates.Y);
}

void UFastNoiseFunctionLibrary::GradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, FVector2D& Coordinates)
{
	return GradientPerturb2D(Seed, Perturb, Frequency, Interpolation, Coordinates.X, Coordinates.Y);
}

void UFastNoiseFunctionLibrary::GradientPerturbFractal2D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, FVector2D& Coordinates)
{
	return GradientPerturbFractal2D(Seed, Perturb, Frequency, Lacunarity, Gain, Octaves, Interpolation, Coordinates.X, Coordinates.Y);
}

float UFastNoiseFunctionLibrary::GetValue3D(int32 Seed, float Frequency, EInterpolation Interpolation, FVector Coordinates)
{
	return GetValue3D(Seed, Frequency, Interpolation, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetValueFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, FVector Coordinates)
{
	return GetValueFractal3D(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetPerlin3D(int32 Seed, float Frequency, EInterpolation Interpolation, FVector Coordinates)
{
	return GetPerlin3D(Seed, Frequency, Interpolation, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetPerlinFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, EFractalType FractalType, FVector Coordinates)
{
	return GetPerlinFractal3D(Seed, Frequency, Lacunarity, Gain, Octaves, Interpolation, FractalType, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetSimplex3D(int32 Seed, float Frequency, FVector Coordinates)
{
	return GetSimplex3D(Seed, Frequency, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetSimplexFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, FVector Coordinates)
{
	return GetSimplexFractal3D(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetWhiteNoise3D(int32 Seed, FVector Coordinates)
{
	return GetWhiteNoise3D(Seed, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetWhiteNoiseInt3D(int32 Seed, FIntVector Coordinates)
{
	return GetWhiteNoiseInt3D(Seed, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetCubic3D(int32 Seed, float Frequency, FVector Coordinates)
{
	return GetCubic3D(Seed, Frequency, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetCubicFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, FVector Coordinates)
{
	return GetCubicFractal3D(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

void UFastNoiseFunctionLibrary::GradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, FVector& Coordinates)
{
	return GradientPerturb3D(Seed, Perturb, Frequency, Interpolation, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

void UFastNoiseFunctionLibrary::GradientPerturbFractal3D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, FVector& Coordinates)
{
	return GradientPerturbFractal3D(Seed, Perturb, Frequency, Lacunarity, Gain, Octaves, Interpolation, Coordinates.X, Coordinates.Y, Coordinates.Z);
}

float UFastNoiseFunctionLibrary::GetSimplex4D(int32 Seed, float Frequency, FVector4 Coordinates)
{
	return GetSimplex4D(Seed, Frequency, Coordinates.X, Coordinates.Y, Coordinates.Z, Coordinates.W);
}

float UFastNoiseFunctionLibrary::GetSimplexFractal4D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves, EFractalType FractalType, FVector4 Coordinates)
{
	return GetSimplexFractal4D(Seed, Frequency, Lacunarity, Gain, Octaves, FractalType, Coordinates.X, Coordinates.Y, Coordinates.Z, Coordinates.W);
}

float UFastNoiseFunctionLibrary::GetWhiteNoise4D(int32 Seed, FVector4 Coordinates)
{
	return GetWhiteNoise4D(Seed, Coordinates.X, Coordinates.Y, Coordinates.Z, Coordinates.W);
}

float UFastNoiseFunctionLibrary::GetWhiteNoiseInt4D(int32 Seed, FIntVector4 Coordinates)
{
	return GetWhiteNoiseInt4D(Seed, Coordinates.X, Coordinates.Y, Coordinates.Z, Coordinates.W);
}

// private 2D
float UFastNoiseFunctionLibrary::SingleValueFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y)
{
	float sum = SingleValue2D(Seed, Interpolation, X, Y);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum += SingleValue2D(Seed, Interpolation, X, Y) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleValueFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y)
{
	float sum = FMath::Abs(SingleValue2D(Seed, Interpolation, X, Y)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		amp *= Gain;
		sum += (FMath::Abs(SingleValue2D(Seed, Interpolation, X, Y)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleValueFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y)
{
	float sum = 1 - FMath::Abs(SingleValue2D(Seed, Interpolation, X, Y));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SingleValue2D(Seed, Interpolation, X, Y))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SingleValue2D(int32 Seed, EInterpolation Interpolation, float X, float Y)
{
	int32 x0 = FMath::Floor(X);
	int32 y0 = FMath::Floor(Y);
	int32 x1 = x0 + 1;
	int32 y1 = y0 + 1;

	float xs, ys;
	switch (Interpolation)
	{
	case EInterpolation::Linear:
		xs = X - (float)x0;
		ys = Y - (float)y0;
		break;
	case EInterpolation::Hermite:
		xs = InterpHermiteFunc(X - (float)x0);
		ys = InterpHermiteFunc(Y - (float)y0);
		break;
	case EInterpolation::Quintic:
		xs = InterpQuinticFunc(X - (float)x0);
		ys = InterpQuinticFunc(Y - (float)y0);
		break;
	}

	float xf0 = FMath::Lerp(SeededCoordinateValue2D(Seed, x0, y0), SeededCoordinateValue2D(Seed, x1, y0), xs);
	float xf1 = FMath::Lerp(SeededCoordinateValue2D(Seed, x0, y1), SeededCoordinateValue2D(Seed, x1, y1), xs);

	return FMath::Lerp(xf0, xf1, ys);
}

float UFastNoiseFunctionLibrary::SinglePerlinFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y)
{
	float sum = SinglePerlin2D(Seed, Interpolation, X, Y);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum += SinglePerlin2D(Seed, Interpolation, X, Y) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);
}

float UFastNoiseFunctionLibrary::SinglePerlinFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y)
{
	float sum = FMath::Abs(SinglePerlin2D(Seed, Interpolation, X, Y)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SinglePerlin2D(Seed, Interpolation, X, Y)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SinglePerlinFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y)
{
	float sum = 1 - FMath::Abs(SinglePerlin2D(Seed, Interpolation, X, Y));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SinglePerlin2D(Seed, Interpolation, X, Y))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SinglePerlin2D(int32 Seed, EInterpolation Interpolation, float X, float Y)
{
	int32 x0 = FMath::Floor(X);
	int32 y0 = FMath::Floor(Y);
	int32 x1 = x0 + 1;
	int32 y1 = y0 + 1;

	float xs, ys;
	switch (Interpolation)
	{
	case EInterpolation::Linear:
		xs = X - (float)x0;
		ys = Y - (float)y0;
		break;
	case EInterpolation::Hermite:
		xs = InterpHermiteFunc(X - (float)x0);
		ys = InterpHermiteFunc(Y - (float)y0);
		break;
	case EInterpolation::Quintic:
		xs = InterpQuinticFunc(X - (float)x0);
		ys = InterpQuinticFunc(Y - (float)y0);
		break;
	}

	float xd0 = X - (float)x0;
	float yd0 = Y - (float)y0;
	float xd1 = xd0 - 1;
	float yd1 = yd0 - 1;

	float xf0 = FMath::Lerp(GradientCoordinateValue2D(Seed, x0, y0, xd0, yd0), GradientCoordinateValue2D(Seed, x1, y0, xd1, yd0), xs);
	float xf1 = FMath::Lerp(GradientCoordinateValue2D(Seed, x0, y1, xd0, yd1), GradientCoordinateValue2D(Seed, x1, y1, xd1, yd1), xs);

	return FMath::Lerp(xf0, xf1, ys);
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y)
{
	float sum = SingleSimplex2D(Seed, X, Y);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum += SingleSimplex2D(Seed, X, Y) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y)
{
	float sum = FMath::Abs(SingleSimplex2D(Seed, X, Y)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SingleSimplex2D(Seed, X, Y)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y)
{
	float sum = 1 - FMath::Abs(SingleSimplex2D(Seed, X, Y));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SingleSimplex2D(Seed, X, Y))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalBlend2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y)
{
	float sum = SingleSimplex2D(Seed, X, Y);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum *= SingleSimplex2D(Seed, X, Y) * amp + 1;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleSimplex2D(int32 Seed, float X, float Y)
{
	float t = (X + Y) * F2;
	int32 i = FMath::Floor(X + t);
	int32 j = FMath::Floor(Y + t);

	t = (i + j) * G2;
	float X0 = i - t;
	float Y0 = j - t;

	float x0 = X - X0;
	float y0 = Y - Y0;

	int32 i1, j1;
	if (x0 > y0)
	{
		i1 = 1; j1 = 0;
	}
	else
	{
		i1 = 0; j1 = 1;
	}

	float x1 = x0 - (float)i1 + G2;
	float y1 = y0 - (float)j1 + G2;
	float x2 = x0 - 1 + 2 * G2;
	float y2 = y0 - 1 + 2 * G2;

	float n0, n1, n2;

	t = float(0.5) - x0 * x0 - y0 * y0;
	if (t < 0) n0 = 0;
	else
	{
		t *= t;
		n0 = t * t * GradientCoordinateValue2D(Seed, i, j, x0, y0);
	}

	t = float(0.5) - x1 * x1 - y1 * y1;
	if (t < 0) n1 = 0;
	else
	{
		t *= t;
		n1 = t * t * GradientCoordinateValue2D(Seed, i + i1, j + j1, x1, y1);
	}

	t = float(0.5) - x2 * x2 - y2 * y2;
	if (t < 0) n2 = 0;
	else
	{
		t *= t;
		n2 = t * t * GradientCoordinateValue2D(Seed, i + 1, j + 1, x2, y2);
	}

	return 70 * (n0 + n1 + n2);
}

float UFastNoiseFunctionLibrary::SingleCubicFractalFbm2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y)
{
	float sum = SingleCubic2D(Seed, X, Y);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum += SingleCubic2D(Seed, X, Y) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleCubicFractalBillow2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y)
{
	float sum = FMath::Abs(SingleCubic2D(Seed, X, Y)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SingleCubic2D(Seed, X, Y)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleCubicFractalRigidMulti2D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y)
{
	float sum = 1 - FMath::Abs(SingleCubic2D(Seed, X, Y));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SingleCubic2D(Seed, X, Y))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SingleCubic2D(int32 Seed, float X, float Y)
{
	int32 x1 = FMath::Floor(X);
	int32 y1 = FMath::Floor(Y);

	int32 x0 = x1 - 1;
	int32 y0 = y1 - 1;
	int32 x2 = x1 + 1;
	int32 y2 = y1 + 1;
	int32 x3 = x1 + 2;
	int32 y3 = y1 + 2;

	float xs = X - (float)x1;
	float ys = Y - (float)y1;

	return CubicLerp(
		CubicLerp(SeededCoordinateValue2D(Seed, x0, y0), SeededCoordinateValue2D(Seed, x1, y0), SeededCoordinateValue2D(Seed, x2, y0), SeededCoordinateValue2D(Seed, x3, y0), xs),
		CubicLerp(SeededCoordinateValue2D(Seed, x0, y1), SeededCoordinateValue2D(Seed, x1, y1), SeededCoordinateValue2D(Seed, x2, y1), SeededCoordinateValue2D(Seed, x3, y1), xs),
		CubicLerp(SeededCoordinateValue2D(Seed, x0, y2), SeededCoordinateValue2D(Seed, x1, y2), SeededCoordinateValue2D(Seed, x2, y2), SeededCoordinateValue2D(Seed, x3, y2), xs),
		CubicLerp(SeededCoordinateValue2D(Seed, x0, y3), SeededCoordinateValue2D(Seed, x1, y3), SeededCoordinateValue2D(Seed, x2, y3), SeededCoordinateValue2D(Seed, x3, y3), xs),
		ys) * CUBIC_2D_BOUNDING;
}

void UFastNoiseFunctionLibrary::SingleGradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y)
{
	float xf = X * Frequency;
	float yf = Y * Frequency;

	int32 x0 = FMath::Floor(xf);
	int32 y0 = FMath::Floor(yf);
	int32 x1 = x0 + 1;
	int32 y1 = y0 + 1;

	float xs, ys;
	switch (Interpolation)
	{
	default:
	case EInterpolation::Linear:
		xs = xf - (float)x0;
		ys = yf - (float)y0;
		break;
	case EInterpolation::Hermite:
		xs = InterpHermiteFunc(xf - (float)x0);
		ys = InterpHermiteFunc(yf - (float)y0);
		break;
	case EInterpolation::Quintic:
		xs = InterpQuinticFunc(xf - (float)x0);
		ys = InterpQuinticFunc(yf - (float)y0);
		break;
	}

	FVector2D Cell2D1 = GCell2D[Hash2D(Seed, x0, y0) & 255];
	FVector2D Cell2D2 = GCell2D[Hash2D(Seed, x1, y0) & 255];
	
	float lx0x = FMath::Lerp(Cell2D1.X, Cell2D2.X, xs);
	float ly0x = FMath::Lerp(Cell2D1.Y, Cell2D2.Y, xs);

	Cell2D1 = GCell2D[Hash2D(Seed, x0, y1) & 255];
	Cell2D2 = GCell2D[Hash2D(Seed, x1, y1) & 255];

	float lx1x = FMath::Lerp(Cell2D1.X, Cell2D2.X, xs);
	float ly1x = FMath::Lerp(Cell2D1.Y, Cell2D2.Y, xs);

	X += FMath::Lerp(lx0x, lx1x, ys) * Perturb;
	Y += FMath::Lerp(ly0x, ly1x, ys) * Perturb;
}

float UFastNoiseFunctionLibrary::SeededCoordinateValue2D(int32 Seed, int32 X, int32 Y)
{
	int32 n = Seed;
	n ^= X_PRIME * X;
	n ^= Y_PRIME * Y;

	return (n * n * n * 60493) / float(2147483648);
}

float UFastNoiseFunctionLibrary::GradientCoordinateValue2D(int32 Seed, int32 X, int32 Y, float Xd, float Yd)
{
	int32 n = Seed;
	n ^= X_PRIME * X;
	n ^= Y_PRIME * Y;
	n = (n * n * n * 60493);

	const FIntPoint Gradient2D = GGradient2DLut[n & 7];
	return Xd * Gradient2D.X + Yd * Gradient2D.Y;
}

// private 3D
float UFastNoiseFunctionLibrary::SingleValueFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z)
{
	float sum = SingleValue3D(Seed, Interpolation, X, Y, Z);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += SingleValue3D(Seed, Interpolation, X, Y, Z) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);
}

float UFastNoiseFunctionLibrary::SingleValueFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z)
{
	float sum = FMath::Abs(SingleValue3D(Seed, Interpolation, X, Y, Z)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SingleValue3D(Seed, Interpolation, X, Y, Z)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleValueFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z)
{
	float sum = 1 - FMath::Abs(SingleValue3D(Seed, Interpolation, X, Y, Z));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SingleValue3D(Seed, Interpolation, X, Y, Z))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SingleValue3D(int32 Seed, EInterpolation Interpolation, float X, float Y, float Z)
{
	int32 x0 = FMath::Floor(X);
	int32 y0 = FMath::Floor(Y);
	int32 z0 = FMath::Floor(Z);
	int32 x1 = x0 + 1;
	int32 y1 = y0 + 1;
	int32 z1 = z0 + 1;

	float xs, ys, zs;
	switch (Interpolation)
	{
	case EInterpolation::Linear:
		xs = X - (float)x0;
		ys = Y - (float)y0;
		zs = Z - (float)z0;
		break;
	case EInterpolation::Hermite:
		xs = InterpHermiteFunc(X - (float)x0);
		ys = InterpHermiteFunc(Y - (float)y0);
		zs = InterpHermiteFunc(Z - (float)z0);
		break;
	case EInterpolation::Quintic:
		xs = InterpQuinticFunc(X - (float)x0);
		ys = InterpQuinticFunc(Y - (float)y0);
		zs = InterpQuinticFunc(Z - (float)z0);
		break;
	}

	float xf00 = FMath::Lerp(SeededCoordinateValue3D(Seed, x0, y0, z0), SeededCoordinateValue3D(Seed, x1, y0, z0), xs);
	float xf10 = FMath::Lerp(SeededCoordinateValue3D(Seed, x0, y1, z0), SeededCoordinateValue3D(Seed, x1, y1, z0), xs);
	float xf01 = FMath::Lerp(SeededCoordinateValue3D(Seed, x0, y0, z1), SeededCoordinateValue3D(Seed, x1, y0, z1), xs);
	float xf11 = FMath::Lerp(SeededCoordinateValue3D(Seed, x0, y1, z1), SeededCoordinateValue3D(Seed, x1, y1, z1), xs);

	float yf0 = FMath::Lerp(xf00, xf10, ys);
	float yf1 = FMath::Lerp(xf01, xf11, ys);

	return FMath::Lerp(yf0, yf1, zs);
}

float UFastNoiseFunctionLibrary::SinglePerlinFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z)
{
	float sum = SinglePerlin3D(Seed, Interpolation, X, Y, Z);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += SinglePerlin3D(Seed, Interpolation, X, Y, Z) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SinglePerlinFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z)
{
	float sum = FMath::Abs(SinglePerlin3D(Seed, Interpolation, X, Y, Z)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SinglePerlin3D(Seed, Interpolation, X, Y, Z)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SinglePerlinFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, EInterpolation Interpolation, float X, float Y, float Z)
{
	float sum = 1 - FMath::Abs(SinglePerlin3D(Seed, Interpolation, X, Y, Z));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SinglePerlin3D(Seed, Interpolation, X, Y, Z))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SinglePerlin3D(int32 Seed, EInterpolation Interpolation, float X, float Y, float Z)
{
	int32 x0 = FMath::Floor(X);
	int32 y0 = FMath::Floor(Y);
	int32 z0 = FMath::Floor(Z);
	int32 x1 = x0 + 1;
	int32 y1 = y0 + 1;
	int32 z1 = z0 + 1;

	float xs, ys, zs;
	switch (Interpolation)
	{
	case EInterpolation::Linear:
		xs = X - (float)x0;
		ys = Y - (float)y0;
		zs = Z - (float)z0;
		break;
	case EInterpolation::Hermite:
		xs = InterpHermiteFunc(X - (float)x0);
		ys = InterpHermiteFunc(Y - (float)y0);
		zs = InterpHermiteFunc(Z - (float)z0);
		break;
	case EInterpolation::Quintic:
		xs = InterpQuinticFunc(X - (float)x0);
		ys = InterpQuinticFunc(Y - (float)y0);
		zs = InterpQuinticFunc(Z - (float)z0);
		break;
	}

	float xd0 = X - (float)x0;
	float yd0 = Y - (float)y0;
	float zd0 = Z - (float)z0;
	float xd1 = xd0 - 1;
	float yd1 = yd0 - 1;
	float zd1 = zd0 - 1;

	float xf00 = FMath::Lerp(GradientCoordinateValue3D(Seed, x0, y0, z0, xd0, yd0, zd0), GradientCoordinateValue3D(Seed, x1, y0, z0, xd1, yd0, zd0), xs);
	float xf10 = FMath::Lerp(GradientCoordinateValue3D(Seed, x0, y1, z0, xd0, yd1, zd0), GradientCoordinateValue3D(Seed, x1, y1, z0, xd1, yd1, zd0), xs);
	float xf01 = FMath::Lerp(GradientCoordinateValue3D(Seed, x0, y0, z1, xd0, yd0, zd1), GradientCoordinateValue3D(Seed, x1, y0, z1, xd1, yd0, zd1), xs);
	float xf11 = FMath::Lerp(GradientCoordinateValue3D(Seed, x0, y1, z1, xd0, yd1, zd1), GradientCoordinateValue3D(Seed, x1, y1, z1, xd1, yd1, zd1), xs);

	float yf0 = FMath::Lerp(xf00, xf10, ys);
	float yf1 = FMath::Lerp(xf01, xf11, ys);

	return FMath::Lerp(yf0, yf1, zs);
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z)
{
	float sum = SingleSimplex3D(Seed, X, Y, Z);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += SingleSimplex3D(Seed, X, Y, Z) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z)
{
	float sum = FMath::Abs(SingleSimplex3D(Seed, X, Y, Z)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SingleSimplex3D(Seed, X, Y, Z)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z)
{
	float sum = 1 - FMath::Abs(SingleSimplex3D(Seed, X, Y, Z));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SingleSimplex3D(Seed, X, Y, Z))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SingleSimplex3D(int32 Seed, float X, float Y, float Z)
{
	float t = (X + Y + Z) * F3;
	int32 i = FMath::Floor(X + t);
	int32 j = FMath::Floor(Y + t);
	int32 k = FMath::Floor(Z + t);

	t = (i + j + k) * G3;
	float X0 = i - t;
	float Y0 = j - t;
	float Z0 = k - t;

	float x0 = X - X0;
	float y0 = Y - Y0;
	float z0 = Z - Z0;

	int32 i1, j1, k1;
	int32 i2, j2, k2;

	if (x0 >= y0)
	{
		if (y0 >= z0)
		{
			i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
		}
		else if (x0 >= z0)
		{
			i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1;
		}
		else // x0 < z0
		{
			i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1;
		}
	}
	else // x0 < y0
	{
		if (y0 < z0)
		{
			i1 = 0; j1 = 0; k1 = 1; i2 = 0; j2 = 1; k2 = 1;
		}
		else if (x0 < z0)
		{
			i1 = 0; j1 = 1; k1 = 0; i2 = 0; j2 = 1; k2 = 1;
		}
		else // x0 >= z0
		{
			i1 = 0; j1 = 1; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
		}
	}

	float x1 = x0 - i1 + G3;
	float y1 = y0 - j1 + G3;
	float z1 = z0 - k1 + G3;
	float x2 = x0 - i2 + 2 * G3;
	float y2 = y0 - j2 + 2 * G3;
	float z2 = z0 - k2 + 2 * G3;
	float x3 = x0 - 1 + 3 * G3;
	float y3 = y0 - 1 + 3 * G3;
	float z3 = z0 - 1 + 3 * G3;

	float n0, n1, n2, n3;

	t = float(0.6) - x0 * x0 - y0 * y0 - z0 * z0;
	if (t < 0) n0 = 0;
	else
	{
		t *= t;
		n0 = t * t * GradientCoordinateValue3D(Seed, i, j, k, x0, y0, z0);
	}

	t = float(0.6) - x1 * x1 - y1 * y1 - z1 * z1;
	if (t < 0) n1 = 0;
	else
	{
		t *= t;
		n1 = t * t * GradientCoordinateValue3D(Seed, i + i1, j + j1, k + k1, x1, y1, z1);
	}

	t = float(0.6) - x2 * x2 - y2 * y2 - z2 * z2;
	if (t < 0) n2 = 0;
	else
	{
		t *= t;
		n2 = t * t * GradientCoordinateValue3D(Seed, i + i2, j + j2, k + k2, x2, y2, z2);
	}

	t = float(0.6) - x3 * x3 - y3 * y3 - z3 * z3;
	if (t < 0) n3 = 0;
	else
	{
		t *= t;
		n3 = t * t * GradientCoordinateValue3D(Seed, i + 1, j + 1, k + 1, x3, y3, z3);
	}

	return 32 * (n0 + n1 + n2 + n3);
}

float UFastNoiseFunctionLibrary::SingleCubicFractalFbm3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z)
{
	float sum = SingleCubic3D(Seed, X, Y, Z);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += SingleCubic3D(Seed, X, Y, Z) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleCubicFractalBillow3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z)
{
	float sum = FMath::Abs(SingleCubic3D(Seed, X, Y, Z)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SingleCubic3D(Seed, X, Y, Z)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleCubicFractalRigidMulti3D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z)
{
	float sum = 1 - FMath::Abs(SingleCubic3D(Seed, X, Y, Z));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SingleCubic3D(Seed, X, Y, Z))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SingleCubic3D(int32 Seed, float X, float Y, float Z)
{
	int32 x1 = FMath::Floor(X);
	int32 y1 = FMath::Floor(Y);
	int32 z1 = FMath::Floor(Z);

	int32 x0 = x1 - 1;
	int32 y0 = y1 - 1;
	int32 z0 = z1 - 1;
	int32 x2 = x1 + 1;
	int32 y2 = y1 + 1;
	int32 z2 = z1 + 1;
	int32 x3 = x1 + 2;
	int32 y3 = y1 + 2;
	int32 z3 = z1 + 2;

	float xs = X - (float)x1;
	float ys = Y - (float)y1;
	float zs = Z - (float)z1;

	return CubicLerp(
		CubicLerp(
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y0, z0), SeededCoordinateValue3D(Seed, x1, y0, z0), SeededCoordinateValue3D(Seed, x2, y0, z0), SeededCoordinateValue3D(Seed, x3, y0, z0), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y1, z0), SeededCoordinateValue3D(Seed, x1, y1, z0), SeededCoordinateValue3D(Seed, x2, y1, z0), SeededCoordinateValue3D(Seed, x3, y1, z0), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y2, z0), SeededCoordinateValue3D(Seed, x1, y2, z0), SeededCoordinateValue3D(Seed, x2, y2, z0), SeededCoordinateValue3D(Seed, x3, y2, z0), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y3, z0), SeededCoordinateValue3D(Seed, x1, y3, z0), SeededCoordinateValue3D(Seed, x2, y3, z0), SeededCoordinateValue3D(Seed, x3, y3, z0), xs),
			ys),
		CubicLerp(
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y0, z1), SeededCoordinateValue3D(Seed, x1, y0, z1), SeededCoordinateValue3D(Seed, x2, y0, z1), SeededCoordinateValue3D(Seed, x3, y0, z1), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y1, z1), SeededCoordinateValue3D(Seed, x1, y1, z1), SeededCoordinateValue3D(Seed, x2, y1, z1), SeededCoordinateValue3D(Seed, x3, y1, z1), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y2, z1), SeededCoordinateValue3D(Seed, x1, y2, z1), SeededCoordinateValue3D(Seed, x2, y2, z1), SeededCoordinateValue3D(Seed, x3, y2, z1), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y3, z1), SeededCoordinateValue3D(Seed, x1, y3, z1), SeededCoordinateValue3D(Seed, x2, y3, z1), SeededCoordinateValue3D(Seed, x3, y3, z1), xs),
			ys),
		CubicLerp(
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y0, z2), SeededCoordinateValue3D(Seed, x1, y0, z2), SeededCoordinateValue3D(Seed, x2, y0, z2), SeededCoordinateValue3D(Seed, x3, y0, z2), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y1, z2), SeededCoordinateValue3D(Seed, x1, y1, z2), SeededCoordinateValue3D(Seed, x2, y1, z2), SeededCoordinateValue3D(Seed, x3, y1, z2), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y2, z2), SeededCoordinateValue3D(Seed, x1, y2, z2), SeededCoordinateValue3D(Seed, x2, y2, z2), SeededCoordinateValue3D(Seed, x3, y2, z2), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y3, z2), SeededCoordinateValue3D(Seed, x1, y3, z2), SeededCoordinateValue3D(Seed, x2, y3, z2), SeededCoordinateValue3D(Seed, x3, y3, z2), xs),
			ys),
		CubicLerp(
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y0, z3), SeededCoordinateValue3D(Seed, x1, y0, z3), SeededCoordinateValue3D(Seed, x2, y0, z3), SeededCoordinateValue3D(Seed, x3, y0, z3), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y1, z3), SeededCoordinateValue3D(Seed, x1, y1, z3), SeededCoordinateValue3D(Seed, x2, y1, z3), SeededCoordinateValue3D(Seed, x3, y1, z3), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y2, z3), SeededCoordinateValue3D(Seed, x1, y2, z3), SeededCoordinateValue3D(Seed, x2, y2, z3), SeededCoordinateValue3D(Seed, x3, y2, z3), xs),
			CubicLerp(SeededCoordinateValue3D(Seed, x0, y3, z3), SeededCoordinateValue3D(Seed, x1, y3, z3), SeededCoordinateValue3D(Seed, x2, y3, z3), SeededCoordinateValue3D(Seed, x3, y3, z3), xs),
			ys),
		zs) * CUBIC_3D_BOUNDING;
}

void UFastNoiseFunctionLibrary::SingleGradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterpolation Interpolation, float& X, float& Y, float& Z)
{
	float xf = X * Frequency;
	float yf = Y * Frequency;
	float zf = Z * Frequency;

	int32 x0 = FMath::Floor(xf);
	int32 y0 = FMath::Floor(yf);
	int32 z0 = FMath::Floor(zf);
	int32 x1 = x0 + 1;
	int32 y1 = y0 + 1;
	int32 z1 = z0 + 1;

	float xs, ys, zs;
	switch (Interpolation)
	{
	default:
	case EInterpolation::Linear:
		xs = xf - (float)x0;
		ys = yf - (float)y0;
		zs = zf - (float)z0;
		break;
	case EInterpolation::Hermite:
		xs = InterpHermiteFunc(xf - (float)x0);
		ys = InterpHermiteFunc(yf - (float)y0);
		zs = InterpHermiteFunc(zf - (float)z0);
		break;
	case EInterpolation::Quintic:
		xs = InterpQuinticFunc(xf - (float)x0);
		ys = InterpQuinticFunc(yf - (float)y0);
		zs = InterpQuinticFunc(zf - (float)z0);
		break;
	}

	FVector Cell1 = GCell3D[Hash3D(Seed, x0, y0, z0) & 255];
	FVector Cell2 = GCell3D[Hash3D(Seed, x1, y0, z0) & 255];
	
	float lx0x = FMath::Lerp(Cell1.X, Cell2.X, xs);
	float ly0x = FMath::Lerp(Cell1.Y, Cell2.Y, xs);
	float lz0x = FMath::Lerp(Cell1.Z, Cell2.Z, xs);

	Cell1 = GCell3D[Hash3D(Seed, x0, y1, z0) & 255];
	Cell2 = GCell3D[Hash3D(Seed, x1, y1, z0) & 255];
	
	float lx1x = FMath::Lerp(Cell1.X, Cell2.X, xs);
	float ly1x = FMath::Lerp(Cell1.Y, Cell2.Y, xs);
	float lz1x = FMath::Lerp(Cell1.Z, Cell2.Z, xs);

	float lx0y = FMath::Lerp(lx0x, lx1x, ys);
	float ly0y = FMath::Lerp(ly0x, ly1x, ys);
	float lz0y = FMath::Lerp(lz0x, lz1x, ys);

	Cell1 = GCell3D[Hash3D(Seed, x0, y0, z1) & 255];
	Cell2 = GCell3D[Hash3D(Seed, x1, y0, z1) & 255];

	lx0x = FMath::Lerp(Cell1.X, Cell2.X, xs);
	ly0x = FMath::Lerp(Cell1.Y, Cell2.Y, xs);
	lz0x = FMath::Lerp(Cell1.Z, Cell2.Z, xs);

	Cell1 = GCell3D[Hash3D(Seed, x0, y1, z1) & 255];
	Cell2 = GCell3D[Hash3D(Seed, x1, y1, z1) & 255];

	lx1x = FMath::Lerp(Cell1.X, Cell2.X, xs);
	ly1x = FMath::Lerp(Cell1.Y, Cell2.Y, xs);
	lz1x = FMath::Lerp(Cell1.Z, Cell2.Z, xs);

	X += FMath::Lerp(lx0y, FMath::Lerp(lx0x, lx1x, ys), zs) * Perturb;
	Y += FMath::Lerp(ly0y, FMath::Lerp(ly0x, ly1x, ys), zs) * Perturb;
	Z += FMath::Lerp(lz0y, FMath::Lerp(lz0x, lz1x, ys), zs) * Perturb;
}

float UFastNoiseFunctionLibrary::SeededCoordinateValue3D(int32 Seed, int32 X, int32 Y, int32 Z)
{
	int32 n = Seed;
	n ^= X_PRIME * X;
	n ^= Y_PRIME * Y;
	n ^= Z_PRIME * Z;

	return (n * n * n * 60493) / float(2147483648);
}

float UFastNoiseFunctionLibrary::GradientCoordinateValue3D(int32 Seed, int32 X, int32 Y, int32 Z, float Xd, float Yd, float Zd)
{
	int32 n = Seed;
	n ^= X_PRIME * X;
	n ^= Y_PRIME * Y;
	n ^= Z_PRIME * Z;

	n = (n * n * n * 60493);
	const FIntVector Gradient3D = GGradient3DLut[n & 15];

	return Xd * Gradient3D.X + Yd * Gradient3D.Y + Zd * Gradient3D.Z;
}

// private 4D
float UFastNoiseFunctionLibrary::SingleSimplexFractalFbm4D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z, float W)
{
	float sum = SingleSimplex4D(Seed, X, Y, Z, W);
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;
		W *= Lacunarity;

		amp *= Gain;
		sum += SingleSimplex4D(Seed, X, Y, Z, W) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalBillow4D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z, float W)
{
	float sum = FMath::Abs(SingleSimplex4D(Seed, X, Y, Z, W)) * 2 - 1;
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;
		W *= Lacunarity;

		amp *= Gain;
		sum += (FMath::Abs(SingleSimplex4D(Seed, X, Y, Z, W)) * 2 - 1) * amp;
	}

	return sum * CalculateFractalBounding(Octaves, Gain);;
}

float UFastNoiseFunctionLibrary::SingleSimplexFractalRigidMulti4D(int32 Seed, float Lacunarity, float Gain, int32 Octaves, float X, float Y, float Z, float W)
{
	float sum = 1 - FMath::Abs(SingleSimplex4D(Seed, X, Y, Z, W));
	float amp = 1;
	int32 i = 0;

	while (++i < Octaves)
	{
		X *= Lacunarity;
		Y *= Lacunarity;
		Z *= Lacunarity;
		W *= Lacunarity;

		amp *= Gain;
		sum -= (1 - FMath::Abs(SingleSimplex4D(Seed, X, Y, Z, W))) * amp;
	}

	return sum;
}

float UFastNoiseFunctionLibrary::SingleSimplex4D(int32 Seed, float X, float Y, float Z, float W)
{
	float n0, n1, n2, n3, n4;
	float t = (X + Y + Z + W) * F4;
	int32 i = FMath::Floor(X + t);
	int32 j = FMath::Floor(Y + t);
	int32 k = FMath::Floor(Z + t);
	int32 l = FMath::Floor(W + t);
	t = (i + j + k + l) * G4;
	float X0 = i - t;
	float Y0 = j - t;
	float Z0 = k - t;
	float W0 = l - t;
	float x0 = X - X0;
	float y0 = Y - Y0;
	float z0 = Z - Z0;
	float w0 = W - W0;

	int32 rankx = 0;
	int32 ranky = 0;
	int32 rankz = 0;
	int32 rankw = 0;

	if (x0 > y0) rankx++; else ranky++;
	if (x0 > z0) rankx++; else rankz++;
	if (x0 > w0) rankx++; else rankw++;
	if (y0 > z0) ranky++; else rankz++;
	if (y0 > w0) ranky++; else rankw++;
	if (z0 > w0) rankz++; else rankw++;

	int32 i1 = rankx >= 3 ? 1 : 0;
	int32 j1 = ranky >= 3 ? 1 : 0;
	int32 k1 = rankz >= 3 ? 1 : 0;
	int32 l1 = rankw >= 3 ? 1 : 0;

	int32 i2 = rankx >= 2 ? 1 : 0;
	int32 j2 = ranky >= 2 ? 1 : 0;
	int32 k2 = rankz >= 2 ? 1 : 0;
	int32 l2 = rankw >= 2 ? 1 : 0;

	int32 i3 = rankx >= 1 ? 1 : 0;
	int32 j3 = ranky >= 1 ? 1 : 0;
	int32 k3 = rankz >= 1 ? 1 : 0;
	int32 l3 = rankw >= 1 ? 1 : 0;

	float x1 = x0 - i1 + G4;
	float y1 = y0 - j1 + G4;
	float z1 = z0 - k1 + G4;
	float w1 = w0 - l1 + G4;
	float x2 = x0 - i2 + 2 * G4;
	float y2 = y0 - j2 + 2 * G4;
	float z2 = z0 - k2 + 2 * G4;
	float w2 = w0 - l2 + 2 * G4;
	float x3 = x0 - i3 + 3 * G4;
	float y3 = y0 - j3 + 3 * G4;
	float z3 = z0 - k3 + 3 * G4;
	float w3 = w0 - l3 + 3 * G4;
	float x4 = x0 - 1 + 4 * G4;
	float y4 = y0 - 1 + 4 * G4;
	float z4 = z0 - 1 + 4 * G4;
	float w4 = w0 - 1 + 4 * G4;

	t = float(0.6) - x0 * x0 - y0 * y0 - z0 * z0 - w0 * w0;
	if (t < 0) n0 = 0;
	else {
		t *= t;
		n0 = t * t * GradientCoordinateValue4D(Seed, i, j, k, l, x0, y0, z0, w0);
	}
	t = float(0.6) - x1 * x1 - y1 * y1 - z1 * z1 - w1 * w1;
	if (t < 0) n1 = 0;
	else {
		t *= t;
		n1 = t * t * GradientCoordinateValue4D(Seed, i + i1, j + j1, k + k1, l + l1, x1, y1, z1, w1);
	}
	t = float(0.6) - x2 * x2 - y2 * y2 - z2 * z2 - w2 * w2;
	if (t < 0) n2 = 0;
	else {
		t *= t;
		n2 = t * t * GradientCoordinateValue4D(Seed, i + i2, j + j2, k + k2, l + l2, x2, y2, z2, w2);
	}
	t = float(0.6) - x3 * x3 - y3 * y3 - z3 * z3 - w3 * w3;
	if (t < 0) n3 = 0;
	else {
		t *= t;
		n3 = t * t * GradientCoordinateValue4D(Seed, i + i3, j + j3, k + k3, l + l3, x3, y3, z3, w3);
	}
	t = float(0.6) - x4 * x4 - y4 * y4 - z4 * z4 - w4 * w4;
	if (t < 0) n4 = 0;
	else {
		t *= t;
		n4 = t * t * GradientCoordinateValue4D(Seed, i + 1, j + 1, k + 1, l + 1, x4, y4, z4, w4);
	}

	return 27 * (n0 + n1 + n2 + n3 + n4);
}

float UFastNoiseFunctionLibrary::SeededCoordinateValue4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W)
{
	int32 n = Seed;
	n ^= X_PRIME * X;
	n ^= Y_PRIME * Y;
	n ^= Z_PRIME * Z;
	n ^= W_PRIME * W;
	
	return (n * n * n * 60493) / float(2147483648);
	
}

float UFastNoiseFunctionLibrary::GradientCoordinateValue4D(int32 Seed, int32 X, int32 Y, int32 Z, int32 W, float Xd, float Yd, float Zd, float Wd)
{
	int32 n = Seed;
	n ^= X_PRIME * X;
	n ^= Y_PRIME * Y;
	n ^= Z_PRIME * Z;
	n ^= W_PRIME * W;

	n = (n * n * n * 60493);
	const FIntVector4 Gradient4D = GGradient4DLut[n & 31];

	return Xd * Gradient4D.X + Yd * Gradient4D.Y + Zd * Gradient4D.Z + Wd * Gradient4D.W;
}

int32 UFastNoiseFunctionLibrary::Hash2D(int32 Seed, const int32& X, const int32& Y)
{

	Seed ^= X_PRIME * X;
	Seed ^= Y_PRIME * Y;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	return Seed;
}

int32 UFastNoiseFunctionLibrary::Hash3D(int32 Seed, const int32& X, const int32& Y, const int32& Z)
{
	Seed ^= X_PRIME * X;
	Seed ^= Y_PRIME * Y;
	Seed ^= Z_PRIME * Z;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	return Seed;
}

int32 UFastNoiseFunctionLibrary::Hash4D(int32 Seed, const int32& X, const int32& Y, const int32& Z, const int32& W)
{
	Seed ^= X_PRIME * X;
	Seed ^= Y_PRIME * Y;
	Seed ^= Z_PRIME * Z;
	Seed ^= W_PRIME * W;

	Seed = Seed * Seed * Seed * 60493;
	Seed = (Seed >> 13) ^ Seed;

	return Seed;
}

float UFastNoiseFunctionLibrary::CalculateFractalBounding(int32 Octaves, float Gain)
{
	float amp = Gain;
	float ampFractal = 1.0f;
	for (int i = 1; i < Octaves; i++)
	{
		ampFractal += amp;
		amp *= Gain;
	}
	return 1.0f / ampFractal;
}


