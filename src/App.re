type status =
  | Started
  | NotStarted;

type action =
  | Start
  | ChangeActiveMole(int);

type state = {
  status,
  activeMole: int,
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {status: NotStarted, activeMole: 0},
  reducer: (action, state) =>
    switch (action) {
    | Start =>
      ReasonReact.UpdateWithSideEffects(
        {...state, status: Started},
        self => {
          let _ =
            Js.Global.setInterval(
              () => {
                let randomInt = Js.Math.random_int(0, 9);
                self.send(ChangeActiveMole(randomInt));
              },
              1000,
            );
          ();
        },
      )
    | ChangeActiveMole(newIndex) =>
      ReasonReact.Update({...state, activeMole: newIndex})
    },
  render: self =>
    <div className="app">
      <div className="game">
        {switch (self.state.status) {
         | NotStarted =>
           <Button text="Start Game!" onClick={_ => self.send(Start)} />
         | Started => <Board activeMole={self.state.activeMole} />
         }}
      </div>
    </div>,
};