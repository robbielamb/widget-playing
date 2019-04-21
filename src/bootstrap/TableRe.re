let component = ReasonReact.statelessComponent("Table");

[@react.component]
let make =
    (
      ~bordered: bool=false,
      ~striped: bool=false,
      ~inverse: bool=false,
      ~hover: bool=false,
      ~reflow: bool=false,
      ~small: bool=false,
      ~responsive: bool=false,
      ~className: option(string)=?,
      ~children,
    ) => {
  let className =
    [
      "table",
      bordered ? "table-bordered" : "",
      striped ? "table-striped" : "",
      inverse ? "table-inverse" : "",
      hover ? "table-hover" : "",
      reflow ? "table-reflow" : "",
      small ? "table-small" : "",
      Utils.unwrapStr(Utils.i, className),
    ]
    |> String.concat(" ");
  let table = <table className> children </table>;
  responsive ? <div className="table-responsive"> table </div> : table;
};