type status =
  | Started
  | NotStarted;

type action =
  | Start
  | ChangeActiveMole(int)
  | Hit(int)
  | Reset
  | Stop;

type state = {
  status,
  score: int,
  activeMole: option(int),
  clickedMole: option(int),
};

let component = ReasonReact.reducerComponent("App");

let initialState = {
  status: NotStarted,
  activeMole: None,
  score: 0,
  clickedMole: None,
};

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch (action) {
    | Stop => ReasonReact.Update(initialState)
    | Reset =>
      ReasonReact.Update({
        ...state,
        score: 0,
        activeMole: None,
        clickedMole: None,
      })
    | Start =>
      ReasonReact.UpdateWithSideEffects(
        {...state, status: Started, clickedMole: None, activeMole: None},
        self => {
          let intervalId =
            Js.Global.setInterval(
              () => {
                let randomInt = Js.Math.random_int(0, 9);
                self.send(ChangeActiveMole(randomInt));
              },
              1000,
            );
          self.onUnmount(() => Js.Global.clearInterval(intervalId));
        },
      )
    | ChangeActiveMole(newIndex) =>
      ReasonReact.Update({
        ...state,
        activeMole: Some(newIndex),
        clickedMole: None,
      })
    | Hit(index) =>
      switch (state.activeMole) {
      | Some(activeMoleIdx) =>
        activeMoleIdx === index ?
          ReasonReact.Update({
            ...state,
            score: state.score + 1,
            clickedMole: Some(index),
            activeMole: None,
          }) :
          ReasonReact.NoUpdate
      | _ => ReasonReact.NoUpdate
      }
    // switch (index) {
    // | idx when Some(idx) === state.activeMole =>
    //   ReasonReact.Update({
    //     ...state,
    //     score: state.score + 1,
    //     clickedMole: Some(index),
    //     activeMole: None,
    //   })
    // | _ => ReasonReact.NoUpdate
    // };
    },
  render: self =>
    <div className="app">
      <div className="game">
        {switch (self.state.status) {
         | NotStarted =>
           <Button text="Start Game!" onClick={_ => self.send(Start)} />
         | Started =>
           <>
             {ReasonReact.string(
                "score: " ++ string_of_int(self.state.score),
              )}
             <button onClick={_ => self.send(Reset)}>
               {ReasonReact.string("reset")}
             </button>
             <button onClick={_ => self.send(Stop)}>
               {ReasonReact.string("stop")}
             </button>
             <Board
               activeMole={self.state.activeMole}
               onClickMole={index => self.send(Hit(index))}
             />
           </>
         }}
      </div>
    </div>,
};