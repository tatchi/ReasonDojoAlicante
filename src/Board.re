let component = ReasonReact.statelessComponent("Board");

let make = (~activeMole, ~onClickMole, _children) => {
  ...component,
  render: _self => {
    <div className="board">
      {Belt.Array.range(0, 8)
       ->Belt.Array.map(index =>
           <div className="board-item" key={string_of_int(index)}>
             <div
               className={
                 "mole"
                 ++ (
                   switch (activeMole) {
                   | Some(i) when i === index => " visible"
                   | _ => ""
                   }
                 )
               }
               onClick={_ => onClickMole(index)}
             />
             <div className="ground" />
           </div>
         )
       ->ReasonReact.array}
    </div>;
  },
};