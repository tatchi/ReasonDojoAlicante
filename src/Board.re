let component = ReasonReact.statelessComponent("Board");

let make = (~activeMole, _children) => {
  ...component,
  render: _self => {
    <div className="board">
      {Belt.Array.range(0, 8)
       ->Belt.Array.map(index =>
           <div className="board-item">
             <div
               className={"mole" ++ (activeMole === index ? " visible" : "")}
             />
             <div className="ground" />
           </div>
         )
       ->ReasonReact.array}
    </div>;
  },
};