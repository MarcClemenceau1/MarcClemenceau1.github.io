/*=============================================================
                    DEFINE CONSTANTS
=============================================================*/
const Head = document.querySelector(`head`);
const Link = document.createElement(`link`);
const GameWrapper = document.querySelector(`.game-wrapper`);
const GameWindow = document.createElement(`section`);
const InfoScreen = document.createElement(`article`);
const InfoScreenTitle = document.createElement(`p`);
const InfoScreenBody = document.createElement(`span`);
const InfoScreenExit = document.createElement(`button`);
const ReelsWrapper = document.createElement(`section`);
const OuterReel = document.createElement(`section`);
const InnerReel = document.createElement(`div`);
const Icon = document.createElement(`img`);
const Icons = [
    `games/game1/images/16.png`,
    `games/game1/images/17.png`,
    `games/game1/images/19.png`,
    `games/game1/images/18.png`,
    `games/game1/images/14.png`,
    `games/game1/images/20.png`,
    `games/game1/images/12.png`,
    `games/game1/images/13.png`,
    `games/game1/images/21.png`,
    `games/game1/images/10.png`
];
const CharacterWrapper = document.createElement(`div`);
const CharacterWrapperInner = document.createElement(`div`);
const CharacterMain = document.createElement(`img`);
const CharacterSwitch = document.createElement(`img`);
const Characters = [
    `games/game1/images/char1.jpg`,
    `games/game1/images/char2.jpg`,
    `games/game1/images/char3.jpg`,
    `games/game1/images/char4.jpg`,
    `games/game1/images/char5.jpg`,
    `games/game1/images/char6.jpg`,
    `games/game1/images/char7.jpg`,
    `games/game1/images/char8.jpg`,
];
const LoadImage1 = new Image().src = `${Icons[0]}`;
const LoadImage2 = new Image().src = `${Icons[1]}`;
const LoadImage3 = new Image().src = `${Icons[2]}`;
const LoadImage4 = new Image().src = `${Icons[3]}`;
const LoadImage5 = new Image().src = `${Icons[4]}`;
const LoadImage6 = new Image().src = `${Icons[5]}`;
const LoadImage7 = new Image().src = `${Icons[6]}`;
const LoadImage8 = new Image().src = `${Icons[7]}`;
const LoadImage9 = new Image().src = `${Icons[8]}`;
const LoadImage10 = new Image().src = `${Icons[9]}`;
const WinBackground = document.createElement(`div`);
const WinningColors = [
    `0`,
    `180`,
    `90`,
    `135`,
    `270`
];
const Rates = [
    0.25,
    0.30,
    0.35,
    0.40,
    0.45,
    0.50,
    0.55,
    0.60,
    0.75,
    3.05
];

const HotBar = document.createElement(`section`);
const HotBarMenuButton = document.createElement(`button`);
const HotBarMenu = document.createElement(`nav`);
const HotBarMenuExit = document.createElement(`button`);
const HotBarMenuInfo = document.createElement(`button`);
const HotBarMenuTurbo = document.createElement(`button`);

const BalanceBetWrapper = document.createElement(`section`);
const BalanceText = document.createElement(`span`);
const BetText = document.createElement(`span`);

const WinText = document.createElement(`span`);
const SpinButton = document.createElement(`button`);
const BetButtonPlus = document.createElement(`button`);
const BetButtonMinus = document.createElement(`button`);

let Balance = 10000;
let Winnings = 0;
let BetSize = 1;
let SpinSpeed = 2000;
let IsSpinning = 0;
let IconHeight = 0;
let InitialIcons = Icons.length - 1;
let CurrentReel = [
    [InitialIcons, InitialIcons, InitialIcons, InitialIcons, InitialIcons],
    [InitialIcons, InitialIcons, InitialIcons, InitialIcons, InitialIcons],
    [InitialIcons, InitialIcons, InitialIcons, InitialIcons, InitialIcons],
    [InitialIcons, InitialIcons, InitialIcons, InitialIcons, InitialIcons],
    [InitialIcons, InitialIcons, InitialIcons, InitialIcons, InitialIcons]
];
let NewReel = [];
let NoiseReel = [];
let NoiseNumber = 40;
let TotalReel = [];
let HotBarMenuClick = 0;
let NoWinAudio = new Audio(`games/game1/audio/nowin.mp3`);
let WinAudio1 = new Audio(`games/game1/audio/win1.mp3`);
let WinAudio2 = new Audio(`games/game1/audio/win2.mp3`);
let WinAudio3 = new Audio(`games/game1/audio/win3.mp3`);
let WinAudio4 = new Audio(`games/game1/audio/win4.mp3`);
let WinAudio5 = new Audio(`games/game1/audio/win6.mp3`);
NoWinAudio.volume = 0.5;
let Chance = {
    win: 0,
    loss: 0
};
/*=============================================================
                        ADD STYLESHEET
=============================================================*/
Head.append(Link);
Link.rel = `stylesheet`;
Link.type = `text/css`;
Link.href = `games/game1/game.css`;

/*=============================================================
                        BUILD MAIN WINDOWS
=============================================================*/
GameWrapper.append(GameWindow, HotBar);
GameWindow.classList.add(`game-window`);
HotBar.classList.add(`hot-bar`);

/*=============================================================
                        BUILD GAME
=============================================================*/
GameWindow.append(InfoScreen, ReelsWrapper, CharacterWrapper);
InfoScreen.append(InfoScreenTitle, InfoScreenBody, InfoScreenExit);
InfoScreen.classList.add(`info-screen`);
InfoScreenTitle.innerHTML = `MARTYS GEMS`;
InfoScreenBody.innerHTML = `To win, you need at least three or more icons in a row vertically / horizontally.<br>ICONS CAN BE CHANGED<br><br>Winnings and balance can not be cashed out as this is only a fictitious game. As you cannot put money in, you cannot take money out.`;
InfoScreenExit.innerHTML = `✕`;
ReelsWrapper.classList.add(`reels-wrapper`);
OuterReel.classList.add(`outer-reel`);
InnerReel.classList.add(`inner-reel`);
for (let i = 0; i < 5; i++) {
    var OuterReelClone = OuterReel.cloneNode();
    ReelsWrapper.append(OuterReelClone);
    OuterReelClone.append(InnerReel.cloneNode());
}
[...document.querySelectorAll(`.inner-reel`)].forEach((element, i) => {
    for (let j = 0; j < 5; j++) {
        let IconClone = Icon.cloneNode();
        IconClone.src = `${Icons[CurrentReel[i][j]]}`;
        element.append(IconClone);
    }
});
// GAME CLICK EVENTS
InfoScreenExit.addEventListener(`click`, () => {
    InfoScreen.style.top = `-50%`;
});
CharacterWrapper.append(CharacterWrapperInner, CharacterSwitch, CharacterMain);
CharacterWrapper.classList.add(`character-wrapper`);
CharacterWrapperInner.classList.add(`character-wrapper-animation`);

CharacterMain.classList.add(`character-main`);
CharacterMain.src = `${Characters[0]}`;

CharacterSwitch.classList.add(`character-switch`);


/*=============================================================
                        BUILD HOTBAR
=============================================================*/
HotBar.append(HotBarMenuButton, HotBarMenu, BalanceBetWrapper, WinText, BetButtonPlus, SpinButton, BetButtonMinus);
HotBarMenuButton.classList.add(`hot-bar-menu-button`);
HotBarMenuButton.innerHTML = `☰`;
HotBarMenu.classList.add(`hot-bar-menu`);
HotBarMenu.append(HotBarMenuExit, HotBarMenuInfo, HotBarMenuTurbo);
HotBarMenuExit.classList.add(`hot-bar-menu-exit`);
HotBarMenuExit.innerHTML = `✕`;
HotBarMenuInfo.innerHTML = `ⓘ Info`;
HotBarMenuTurbo.innerHTML = `&#x23e9; Turbo`;
BalanceBetWrapper.classList.add(`balance-bet-wrapper`);
BalanceBetWrapper.append(BalanceText, BetText);
BalanceText.innerHTML = `BALANCE $${Balance}`;
BetText.innerHTML = `BET $${BetSize}`;
WinText.classList.add(`win-text`);
BetButtonPlus.classList.add(`bet-spin-button-plus`);
BetButtonPlus.innerHTML = `+`;
SpinButton.classList.add(`spin-button`);
SpinButton.innerHTML = `&#8635;`;
BetButtonMinus.classList.add(`bet-spin-button-minus`);
BetButtonMinus.innerHTML = `&#8722;`;
// HOT BAR CLICK EVENTS
[HotBarMenuButton, HotBarMenuExit].forEach((element) => {
    element.addEventListener(`click`, () => {
        if (HotBarMenuClick === 0) {
            HotBarMenu.style.left = 0;
            HotBarMenuClick = 1;
        } else {
            HotBarMenu.style.left = `-${HotBarMenu.offsetWidth}px`;
            HotBarMenuClick = 0;
        }
    });
});
HotBarMenuInfo.addEventListener(`click`, () => {
    HotBarMenuClick = 0;
    HotBarMenu.style.left = `-${HotBarMenu.offsetWidth}px`;
    InfoScreen.style.top = `50%`;
});
HotBarMenuTurbo.addEventListener(`click`, () => {
    HotBarMenuClick = 0;
    HotBarMenu.style.left = `-${HotBarMenu.offsetWidth}px`;
    if (SpinSpeed === 2000) {
        SpinSpeed = 300;
        HotBarMenuTurbo.style.color = `var(--theme1)`;
    } else {
        SpinSpeed = 2000;
        HotBarMenuTurbo.style.color = `var(--text)`;
    }
});
BetButtonPlus.addEventListener(`click`, () => {
    BetSize == 1 ? BetSize += 9 : BetSize = Math.min(BetSize + 10, 1000)
    BetText.innerHTML = `BET $${BetSize}`;
    BetText.style.scale = `1.05`;
    BetSize = Math.min(BetSize, Balance);
BetText.innerHTML = `BET $${BetSize}`;
    setTimeout(() => {
        BetText.style.scale = `1`;
    }, 50);
});
BetButtonMinus.addEventListener('click', () => {
    if (BetSize > 1000) {
        BetSize = 1000;
    } else {
        BetSize = Math.max(BetSize - 10, 1);
    }
    BetText.innerHTML = `BET $${BetSize}`;
    BetText.style.scale = '0.95';
    setTimeout(() => {
        BetText.style.scale = '1';
    }, 50);
});

SpinButton.addEventListener(`click`, (element) => {
    let CurrentTarget = element.currentTarget;
    CurrentTarget.style.transition = `rotate 400ms ease`;
    CurrentTarget.style.rotate = `360deg`;
    CurrentTarget.disabled = true;
    CurrentTarget.style.opacity = 0.5;

    Spin(BetSize, SpinSpeed, () => {
        setTimeout(() => {
            CurrentTarget.style.transition = 'none';
            CurrentTarget.style.rotate = '0deg';
            CurrentTarget.disabled = false;
            CurrentTarget.style.opacity = 1;
            BalanceText.innerHTML = `BALANCE $${Balance}`;
            
            if(Winnings == 0){
                WinText.innerHTML = `$${Winnings}`;
                if(Balance <= 0){
                    Balance = 100;
                    BetSize = Math.min(BetSize, Balance); // Ensure bet size does not exceed balance
                    BalanceText.innerHTML = `BALANCE $100`;
                    BetText.innerHTML = `BET $100`; // Reset bet display to $100
                }
            } else {
                WinText.innerHTML = `WIN $${Winnings}`;
            }
        }, SpinSpeed + 450);
    });
    
});
// Assuming you have an 'allInButton' with the id 'allInButton' in your HTML
document.getElementById('allInButton').addEventListener('click', function() {
    // Set BetSize to the total balance available
    BetSize = Balance;

    // Update the BetText to reflect the new BetSize
    BetText.innerHTML = `BET $${BetSize}`;

    // Trigger the spin with the new BetSize
    SpinButton.click();
});


document.body.onkeyup = function(e){
    e.preventDefault();
    if(e.keyCode == 32 || e.keyCode == 13){
        if(IsSpinning == 0){
            let CurrentTarget = SpinButton;
            CurrentTarget.style.transition = `rotate 400ms ease`;
            CurrentTarget.style.rotate = `360deg`;
            CurrentTarget.disabled = true;
            CurrentTarget.style.opacity = 0.5;
            IsSpinning = 1;
        
            Spin(BetSize, SpinSpeed, () => {
                setTimeout(() => {
                    CurrentTarget.style.transition = `none`;
                    CurrentTarget.style.rotate = `0deg`;
                    CurrentTarget.disabled = false;
                    CurrentTarget.style.opacity = 1;
                    IsSpinning = 0;
                    BalanceText.innerHTML = `BALANCE $${Balance}`;
                    if(Winnings == 0){
                        WinText.innerHTML = `$${Winnings}`;
                    }else{
                        WinText.innerHTML = `WIN $${Winnings}`;
                    }
                }, SpinSpeed + 450);
            });
        }
    }
}

/*=============================================================
                    SPINT FUNCTION
=============================================================*/
function Spin(fnBetSize = 1, fnSpinSpeed = 2000, fnCallBack){
    if(Balance >= fnBetSize){
        Balance -= fnBetSize;

        document.querySelectorAll(`.win-background`).forEach(e => e.remove());

        NewReel = [];
        for(let i = 0; i < 5; i++){
            let TempReel = [];
            for(let j = 0; j < 5; j++){
                TempReel.push(Math.floor(Math.random() * Icons.length + 0));
            }
            NewReel.push(TempReel);
        }

        if(fnSpinSpeed == 300){
            NoiseNumber = 0;
        }else{
            NoiseNumber = 30;
        }

        NoiseReel = [];
        for(let i = 0; i < 5; i++){
            let TempReel = [];
            for(let j = 0; j < NoiseNumber; j++){
                TempReel.push(Math.floor(Math.random() * Icons.length + 0));
            }
            NoiseReel.push(TempReel);
        }

        let GetInnerReels = document.querySelectorAll(`.inner-reel`);
        for(let i = 0; i < GetInnerReels.length; i++){
            GetInnerReels[i].innerHTML = ``;
            TotalReel = [];
            TotalReel = [NewReel[i], NoiseReel[i], CurrentReel[i]];
            for(let j = 0; j < TotalReel.length; j++){
                for(let k = 0; k < TotalReel[j].length; k++){
                    let IconClone = Icon.cloneNode();
                    GetInnerReels[i].append(IconClone);
                    IconClone.src = Icons[TotalReel[j][k]];
                }
            }

            GetInnerReels[i].style.transition = `bottom ${fnSpinSpeed}ms ease`;
            GetInnerReels[i].style.transitionDelay = `${i * 100}ms`;
            GetInnerReels[i].style.bottom = `calc(-${GetInnerReels[i].offsetHeight}px + 100%)`;


            setTimeout(() => {
                GetInnerReels[i].innerHTML = ``;
                for(let j = 0; j < NewReel[i].length; j++){
                    let IconClone = Icon.cloneNode();
                    GetInnerReels[i].append(IconClone);
                    IconClone.src = Icons[NewReel[i][j]];
                }
                
                GetInnerReels[i].style.transition = `none`;
                GetInnerReels[i].style.bottom = `0`;
            }, fnSpinSpeed + 450);
        }

        // CHECK FOR WINNINGS
        let Visited = [];
        let Counter = 0;
        for(let i = 0; i < NewReel.length; i++){
            for(let j = 0; j < NewReel[i].length; j++){
                Visited.push({
                    id: Counter,
                    position: `${i}:${j}`,
                    icon: NewReel[i][j]
                });
                Counter++;
            }
        }
        Counter = 0;
        for(let i = 0; i < NewReel.length; i++){
            for(let j = 0; j < NewReel[i].length; j++){
                try{
                    if(NewReel[i][j] == NewReel[i][j - 1]){
                        Visited[Counter].id = Visited[Counter - 1].id;
                    }
                }catch(e){}
                try{
                    if(NewReel[i][j] == NewReel[i - 1][j]){
                        Visited[Counter].id = Visited[Counter - 5].id;
                    }
                }catch(e){}
                try{
                    if(NewReel[i][j] == NewReel[i][j - 1] && NewReel[i][j] == NewReel[i - 1][j]){
                        Visited[Counter].id = Visited[Counter - 5].id;

                        let MatchValue = Counter - 5;
                        for(let k = 1; k <= j; k++){
                            let CurrentPosition = Counter - k;
                            if(NewReel[i][j] == NewReel[i][j - k]){
                                Visited[CurrentPosition].id = Visited[Counter - 5].id;
                                try{
                                    if(NewReel[i][j - k] == NewReel[i - 1][j - k] && k != 1){
                                        for(let l = Visited.length - 1; l >= 0; l--){
                                            if(Visited[l].id == Visited[MatchValue].id){
                                                Visited[l].id = Visited[CurrentPosition - 5].id;
                                            }
                                        }
                                    }
                                }catch(e){}
                            }else{
                                break;
                            }
                        }
                    }
                }catch(e){}
                Counter++;
            }
        }

        let UniqueAll = [];
        let Element = ``;
        for(let i = 0; i < Visited.length; i++){
            Element = Visited[i].id;
            if(!UniqueAll[Element]) UniqueAll[Element] = [];
            UniqueAll[Element].push(Visited[i]);
        }
        let UniqueOverThree = [];
        for(let i = 0; i < UniqueAll.length; i++){
            try{
                if(UniqueAll[i].length >= 3){
                    UniqueOverThree.push(UniqueAll[i]);
                }
            }catch(e){}
        }


        setTimeout(() => {
            NoWinAudio.pause();
            WinAudio1.pause();
            WinAudio2.pause();
            WinAudio3.pause();
            WinAudio4.pause();
            WinAudio5.pause();
    
            NoWinAudio.currentTime = 0;
            WinAudio1.currentTime = 0;
            WinAudio2.currentTime = 0;
            WinAudio3.currentTime = 0;
            WinAudio4.currentTime = 0;
            WinAudio5.currentTime = 0;
            CharacterSwitch.classList.remove(`character-switch-animation`);
            void CharacterSwitch.offsetHeight;

            let BestMatch = 0;
            Winnings = 0;
            for(let i = 0; i < UniqueOverThree.length; i++){
                for(let j = 0; j < UniqueOverThree[i].length; j++){
                    let PositionX = UniqueOverThree[i][j].position.split(`:`)[0] * 20;
                    let PositionY = UniqueOverThree[i][j].position.split(`:`)[1] * 20;

                    if(UniqueOverThree[i][j].icon == Icons.length - 1) BestMatch = 1;

                    let WinBackgroundClone = WinBackground.cloneNode();
                    ReelsWrapper.append(WinBackgroundClone);
                    WinBackgroundClone.classList.add(`win-background`);
                    WinBackgroundClone.style.top = `${PositionY}%`;
                    WinBackgroundClone.style.left = `${PositionX}%`;
                    WinBackgroundClone.style.filter = `hue-rotate(${WinningColors[i]}deg)`;
                }

                let WinningIcon = UniqueOverThree[i][0].icon;
                let WinningStreaks = UniqueOverThree[i].length;
                Balance = Balance + (((fnBetSize * Rates[WinningIcon]) * WinningStreaks));
                Balance = Number(Math.round(Balance + 'e' + 2) + 'e-' + 2);
                Winnings += ((fnBetSize * Rates[WinningIcon]) * WinningStreaks);
            }
            Winnings = Number(Math.round(Winnings + 'e' + 2) + 'e-' + 2);

            if(UniqueOverThree.length == 0){
                CharacterWrapperInner.classList.remove(`character-wrapper-animation`);
                CharacterWrapperInner.style.animationDelay = `0ms`;
                void CharacterWrapperInner.offsetHeight;
                CharacterWrapperInner.classList.add(`character-wrapper-animation`);
                NoWinAudio.play();
            }else{
                if(BestMatch === 1){
                    WinAudio5.play();
                    CharacterSwitch.src = `${Characters[7]}`;
                }else{
                    if(UniqueOverThree.length === 1){
                        WinAudio2.play();
                        CharacterSwitch.src = `${Characters[2]}`;
                    }
                    if(UniqueOverThree.length === 2){
                        WinAudio1.play();
                        CharacterSwitch.src = `${Characters[4]}`;
                    }
                    if(UniqueOverThree.length === 3){
                        WinAudio3.play();
                        CharacterSwitch.src = `${Characters[5]}`;
                    }
                    if(UniqueOverThree.length === 4){
                        WinAudio4.play();
                        CharacterSwitch.src = `${Characters[6]}`;
                    }
                }
                CharacterSwitch.classList.add(`character-switch-animation`);
            }
        }, fnSpinSpeed + 450);

        CurrentReel = NewReel;
        fnCallBack();
    }
}