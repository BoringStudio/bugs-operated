#pragma once

#include "SceneManager.h"
#include "FontFactory.h"

#include "Constants.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

/*
                                        ``..--:/++oso+:.                        
                                 `..-:/+ooosssssssoshhhy/`                      
                               `/ssssssssssyyysyssydNNdhh+`                     
                               .ydhhhhyyyyyyyyyyyydNNNmhhh+`                    
                                :dddddddhhhhyyyyhhhddddhhhhs-                   
                                 /dNmmmmmdddddhyyyyhhhhhhhhhh/`                 
                                  :hNNNNNNmmmmdddhhyyyyyyyyyhh-                 
                                   .sNNNNNNNNNNNmmmddhhyyyyyyho`                
                                    `+dNNNNNNNmmmmmmmmddhyyyyyy:`               
                                      .odmmmmmmmdddddddhhyysyyhy-               
                                        /dmdddddddddhhhyyyssssyho.              
                                        .ydddddddhhhhhyyysssssyyh+              
                                        -yddhhhhhhhhhhyyysssssyyhd/             
                                       .ohdhhhhhhhhhhhhhyyyssyyhddh:            
                                     `-shhddhhhhhhhhhhhhhhyyssyyhhhy-           
                              ``.-:/+syhhdddhddhhhhhhhhhhhhhssssyhyhy-          
                        ````-:+syhhhhhhhdmdddddhhhhhhhhhhhhhhyyyyyyhdy.         
                    `.-::/+ossyhhhhhhdddho-+dddhhhhhyyyhhhhhhdhyysyyhdo         
               `.-:++ossssyyyhhhhhddmms:.``sddhhhhhyyyyyyhhhhddhyssyyhh:..-:.   
            `-/osssssyyyyhdddddddhyo/.    -hdhhhhyyyyyyyhhhhhhhhhhysssyysys:`   
        `.-/oyyyyyhhhdddmmdh+:--.`        /ddhhhyyyyyyyhhhhhhhhyyhyysyhyo-      
```...-:+oyhhddddddddys+/-.`              oddhhhyyyyyyyhhhhhhhhyyyyyhdm+ `      
yyyyhhhhhhdmmo:::-.``                     sdddhhhhhyyhhhhhhhhhhyyyhhddm/        
.-:ohmmNNNNmo`                            sdddhhhhhhhhhhhhhhhhyyhhhhhdd.        
   .--.-so.`                              :ddddhhhhhhhhhhhhhhhhhhhhyydd-        
                                          .ymdddddddddddhddddddhddhysyh:`       
                                          `omdddddddddddddddddddddhyssyh/`      
                                         `shdddddddddddddddddddddddhysyyho-`    
                                        -shhhddmdddddddddddddddmmdddyssyyhd+`   
                                       -yhhhhhhdmmmmmmdddddddmmmmmmdhysyyhhh:`  
                                      -sdhhhhhdddmmmmmmmmmmmmmmmNNmdhysyyyhhy:` 
                                     -ydhhddddddddmmmmmmmmmmmmmmNNNmhysyyhhhhh/ 
                                    -ydhdddddddmmmmmNmhydmNNNNNNNmNmdyyyyyhhhhs`
                                   .sdhdddmmmmmmmNmd+://oydNNNNNNNNmdhyysyyyhhh:
                                  .odddddmmmmNNmhsoohmNNNmddddhdmmmNmhyyyyyhhhdo
                                `+yhddmmmmNmds/:ohdmmmmmmdhhhdhdmNNNmdhyyyyhhhdh
                               .odhdmmNNds+-`  /ddddmdhdmdhhyssyyyo+ohdhyyyhhhdd
                              `+hhddmNh:.      `------./hs.```` `    +dhyyyhhhdh
                              -yhhdmmNy.               :hs`          `odhyyhhhds
                              :hhyhhdmNh:              -y/            `sdyyhhhd/
                              .odhhhhddmd+`           `:y/             :hyyhhdd-
                               `+hhhhhhdmms-          `+h/            `+yyyhhdy.
                                `:ohhhhhddmh:         `+y:           `+ysssyhd+`
                                   .oyhhhhdmd/`      -/oo+-`        `/ysosyyhd/ 
                                    ``/shhhhdms.   `.oyyoos:        -sysssyhhd/ 
                                       `.:shhhmdssyddmmmyoss+-.`   `+hyssyyhdh: 
                                          `+hdmmNNNNNNNNh+smNNmh+. .yhyyyyhhdy. 
                                        `:smdmmmNNmNNmmNh+ymNNNNNmsohysyyyhhd/  
                                      `/hmmmmmmdmmmNmmdssoymNNNNNNNmhyyyyhhdh-  
                                     -yddmNmhdmh+ohdddy-oohhdhdNNNNdyyyyyhdmo`  
                                   `oddmmdhdmmmmmmhyddy-+shhy``:yNmhyyyyhhdd-   
                                  -yddmmhdyoydmmmddyhdo.+sdm/ ``ohdhyyyyhdmo`   
                                 -yddmdydo` `:dms.:shd/./sds` `/ysdyyyyhhdd-    
                                .yddNhyhh+`   -mm:-ssd+:ssh: `/dhohyyyyhdmy`    
                               .ymdmdhNs.os.   -dh:+sh+:oy+` -ds-ohyyyhhdmN/    
                              `+ddmhym-/yo/y+`  :hdosh+-oo- .h/`.yhyyyhdmmNd-   
                              -hdmdyd/  `:oyhs-  :hsody:o+./h:  /hyyyhddmmmN/   
                             `odmmhds`    `-odd/``odsddsoood/`./hhyyyhdmNmmNy`  
                             -dmmdyh++/:.`   ./ys:/hddmh+hm+./ysyhyyhdsommmmd-  
                             /ddNhydsoosss+:.` `/yyyddhhodyos/..ohyhdmysmmmmm:  
                            `smmNyd+.-::+osyyyo/:+hhdmmdoddo-.:+yyyhds/+mNmmm:  
                            .hmmmyd:     ````.-/shhddmds+sssyssyysyds:./mNmmm:  
                            `dmmmyh-```.-.-::/+oyhhdmmdysssso-:yyyhh-  -mNmmm:  
                            `dmmmyd++o+oyhhdys+//+sdmmmNdsy/ohyysydy:..+mmdmd-  
                            .dmmmyms+oo+/:-.`.-shsodhdmmyoso:/yyshdyooodNmdNy`  
                            .hmmmhms-`    `.+hds:odsymNNso+:ohysydo:++odmmdNo   
                            `ommmddy.  `./osyo-.smo:dhdNyoy:-yyyhh.  `sNmdmd-   
                             -dmmdhm/./ooyy+.`-yms.smohNyoddsysydy-` -dNddN+    
                             `ymmmhdds++so-` :yhs.:mh-sms+smdsydy:/+:smmdmd.    
                              :dmmmdmys/.  `/ssy..smo`+mso/yhshd/``:hmmdmm/     
                               +mmmdhms`  `+ysy. /hh:`omoo:+syds. -yNmdmm/`     
                               .hNmmdhmo``sssy- .syy``omoo/oyhho./hNmddm+`      
                                .dNmmmdmhy+oh-  /yyo  +do+:shyyyyddmdmm+`       
                                 .yNmmmddmhy-  .ysy:  -sohhmmmdhhyyyyho`        
                                  `omNmmmdmdy/./yos`  :yydhmmmmmNmmms:/`        
                                   `:hNNmmmmmmdmhhs/:+ymmNNNmmmmmNh/`           
                                     `/hNmmmmmmmmmmmmNNmNNNNmmmmh/`             
                                       `-ohmNmNmmmmmmmNNNNNNNh+-                
                                          `.+shdNNNNNNNNdyo/.`                  
*/

class Intro : public Scene
{
public:
	Intro();

	void onInit() override;
	void onClose() override;
	void onLeave() override;
	void onReturn() override;

	void onUpdate(const float dt) override;
	void onDraw(const float dt) override;

	void onResize(const vec2& windowSize) override;
	void onFocusLost() override;
	void onFocusGained() override;

private:
	sf::RectangleShape m_introRect;
	sf::RectangleShape m_blackScreen;
	sf::Color m_clearColor;

	sf::Text m_studioName;

	float m_speedDelay;
	float m_alpha;
	float m_sinStep;
	float m_blackScreenDelay;
	float m_blackScreenDt;

	bool m_hasEnableAnimation;
};